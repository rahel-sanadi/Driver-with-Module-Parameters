Assignment 1: Asset Tracking – Simulate Sensor Data Packaging and API Integration
-------------------------------------------------------------------------------

## Overview
This project simulates an asset tracking device that generates sensor data
(temperature and GPS coordinates), packages the data into a hex-encoded payload,
and processes downlink messages to update the reporting interval.

The program is implemented in C, split into multiple files (`main.c`, `api.c`,
`sensor.c`), with clear modularity. It is a software-only simulation.

-------------------------------------------------------------------------------
## Files in the Project
- main.c       : Contains the main simulation logic and test case handling.
- api.c/h      : Implements the data packaging and downlink parsing APIs.
- sensor.c/h   : Generates random temperature, latitude, and longitude values.
- Makefile     : (Optional) Automates compilation using `make`.
- README.txt   : Instructions and assumptions.

-------------------------------------------------------------------------------
## Features
1. **Random Sensor Data**
   - Temperature between -20.0°C and 50.0°C.
   - Latitude between -90.0° and 90.0°.
   - Longitude between -180.0° and 180.0°.

2. **Hex-Encoded Payload**
   - Data is packaged into a compact binary format and printed as hex.

3. **Downlink Message Parsing (Bonus)**
   - Parses a 4-byte hex string (8 hex characters) to extract the reporting interval (in seconds).
   - Example: "0000003C" = 60 seconds.

4. **User Input**
   - Allows user-provided sensor values or random generation.
   - User can select and run 5 different test cases.

-------------------------------------------------------------------------------
## Test Cases
The program supports 5 test cases as per assignment requirements:

1. **Normal Run**
   - Input: Random or user-defined temp/lat/lon; hex `0000003C` (60s).
   - Output: Valid payload; interval = 60s.

2. **Data Limits**
   - Input: Min (-20.0°C, -90.0, -180.0) and Max (50.0°C, 90.0, 180.0); hex `000000FF` (255s).
   - Output: Valid payloads; interval = 255s.

3. **API Fail**
   - Input: Random data; hex `INVALID`.
   - Output: Error message and non-zero exit.

4. **Empty Payload**
   - Input: No payload; hex `0000001E` (30s).
   - Output: Empty payload; interval = 30s.

5. **Interval Variety (Bonus)**
   - Input: hex `00000001` (1s), `00000384` (900s).
   - Output: Interval = 1s and 900s.

-------------------------------------------------------------------------------
## How to Compile in vs code

### Option 1: 
Compile:
    gcc main.c api.c sensor.c -o asset_tracking
Run:
    ./asset_tracking

-------------------------------------------------------------------------------


