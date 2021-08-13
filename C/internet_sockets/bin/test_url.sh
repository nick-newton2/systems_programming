#!/bin/bash

UNIT=bin/unit_url
WORKSPACE=/tmp/url.$(id -u)
FAILURES=0

error() {
    echo "$@"
    [ -r $WORKSPACE/test ] && (echo; cat $WORKSPACE/test; echo)
    FAILURES=$((FAILURES + 1))
}

cleanup() {
    STATUS=${1:-$FAILURES}
    rm -fr $WORKSPACE
    exit $STATUS
}

export LD_LIBRARY_PATH=$LD_LIBRRARY_PATH:.

mkdir $WORKSPACE

trap "cleanup" EXIT
trap "cleanup 1" INT TERM

echo "Testing url..."

if [ ! -x $UNIT ]; then
    echo "Failure: $UNIT is not executable!"
    exit 1
fi

TESTS=$($UNIT 2>&1 | tail -n 1 | awk '{print $1}')
for t in $(seq 0 $TESTS); do
    desc=$($UNIT 2>&1 | awk "/$t/ { print \$3 }")

    printf " %-50s ... " "$desc"
    valgrind --leak-check=full $UNIT $t &> $WORKSPACE/test
    if [ $? -ne 0 ] || [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
	error "Failure"
    else
	echo "Success"
    fi
done

TESTS=$(($TESTS + 1))

echo
echo "   Score $(echo "scale=4; ($TESTS - $FAILURES) / $TESTS.0 * 2.5" | bc | awk '{ printf "%0.2f\n", $1 }' )"
echo
