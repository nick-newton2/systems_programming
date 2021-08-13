#!/bin/sh

# Globals

URL="https://forecast.weather.gov/zipcity.php"
ZIPCODE=46556
FORECAST=0
CELSIUS=0

# Functions

usage() {
    cat 1>&2 <<EOF
Usage: $(basename $0) [zipcode]
-c    Use Celsius degrees instead of Fahrenheit for temperature
-f    Display forecast text
If zipcode is not provided, then it defaults to $ZIPCODE.
EOF
    exit $1
}

weather_information() {
    # Fetch weather information from URL based on ZIPCODE
    curl -sL "$URL?inputstring=$ZIPCODE"
}

temperature() {
    # Extract temperature information from weather source
    if [ "$CELSIUS" = "1" ]; then
      weather_information | grep -Eo 'myforecast.*deg;C'|cut -d '>' -f 2| cut -d '&' -f 1
    else
      weather_information | grep -Eo 'myforecast.*deg;F'|cut -d '>' -f 2| cut -d '&' -f 1
    fi
}

forecast() {
    # Extract forecast information from weather source
    weather_information | grep -Eo 'myforecast-current.*>[a-zA-Z ].*'|cut -d '>' -f 2 |cut -d '<' -f 1| sed 's/ //g'
}

# Parse Command Line Options

while [ $# -gt 0 ]; do
    case $1 in
        -c) CELSIUS=1 ;;
        -f) FORECAST=1 ;;
        [0-9][0-9][0-9][0-9][0-9]) ZIPCODE=$1 ;;
        -h) usage 0;;
         *) usage 1;;
    esac
    shift
done

# Display Information
if [ "$FORECAST" = "1" ]; then
  echo "Forecast:    $(forecast)"
fi

echo "Temperature: $(temperature) degrees"
