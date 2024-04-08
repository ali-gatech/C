#!/bin/bash

./sim ../traces/$1 >> $2

python3 fingerprint.py $2