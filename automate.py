#!/usr/bin/env python

import serial
import serial.tools.list_ports
import io

# Connect to a device matching what we want
# port = list(list_ports.grep(r"/dev/cu.usbmodem*"))[0]
port = "COM17"
ser = serial.Serial(port, 115200, timeout=1)
sio = io.TextIOWrapper(io.BufferedRWPair(ser, ser))

def run_cmd(cmd):
    # Write our command and send immediately
    sio.write(f"{cmd}\n")
    sio.flush()

    # Our serial implementation prints the input to the shell
    command = sio.readline()
    # Read the response on the next line
    response = sio.readline()
    # output to user
    print(response)

# Run full test-suite on target
run_cmd("hello")
run_cmd("led_io 1 1")
run_cmd("led_io 1 0")
run_cmd("led_io 2 1")
run_cmd("led_io 2 0")
run_cmd("led_io 3 1")
run_cmd("led_io 3 0")

print("Done.")