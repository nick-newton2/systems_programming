#!/bin/sh

# Globals
CITY=".*"
STATE="Indiana"

URL=https://www.zipcodestogo.com/

# Functions

usage() {
  cat 1>&2 <<EOF
Usage: $(basename $0)
  -c CITY specify a specific city
  -s STATE specify a specific state
EOF
  exit $1
}

# Parse Command Line Options

while [ $# -gt 0 ]; do
    case $1 in
    -s) STATE=$2 ; shift ;;
    -c) CITY=$2; shift ;;
    -h) usage 0;;
     *) usage 1;;
    esac
    shift
done

# Filter Pipeline(s)

STATE=$(echo $STATE| sed 's/ /%20/g')
curl -s $URL$STATE/ |grep -E "zipcodestogo.com/$CITY/[A-Z][A-Z]/" | cut -d '/' -f 6
