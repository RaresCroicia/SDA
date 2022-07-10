#!/bin/bash

SRC=ex"$1".c
EXEC=ex"$1"

gcc -o $EXEC $SRC -lm
./"$EXEC"
