#!/bin/sh

sum() {
    result=0

    for value; do
        result=$(expr "$result" + "$value" 2>/dev/null)
        if [ $? -ne 0 ]; then
            echo 0
            return 1
        fi
    done

    echo "$result"
    return 0
}

IFS= read -r line1
IFS= read -r line2

first=$(sum $line1)
second=$(sum $line2)

if [ "$first" = "$second" ]; then
    echo Equal
else
    echo "Not equal"
fi
