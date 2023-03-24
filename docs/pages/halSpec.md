
# TV Settings HAL Documentation

## Version History

| Date | Author | Comment | Version |
| --- | --------- | --- | --- |
| 24/03/23 | Review Team | Edited | 1.0.3 |
| 23/03/23 | Thanushree Rajaselvam | Addressed comments | 1.0.2 |
| 20/03/23 | Review Team | Edited | 1.0.1 |
| 16/11/22 | Aishwariya Bhaskar | First Release | 1.0.0 |

## Acronyms #TODO: convert to table

| Acronym | Expansion |
| --- | --------- |
| CPU| Central Processing Unit |
| HAL| Hardware Abstraction layer |
| PQ| Picture Quality |
| SOC| System on chip |
| OEM| Original Equipment Manufacturer |
| ALS| Auto Light Sensor |

## Description

TV Settings HAL is an abstract layer, which provides APIs to Modify/Control the Picture quality parameters, dimming modes and auto backlight modes.

```mermaid
%%{ init : { "theme" : "forest", "flowchart" : { "curve" : "linear" }}}%%
flowchart TD
Caller --> x[TV Setting HAL] 
x[TV Setting HAL] --> y[Video/PictureQuality Driver]
style Caller fill:#99CCFF,stroke:#333,stroke-width:0.3px
style y fill:#fc9,stroke:#333,stroke-width:0.3px
style x fill:#9f9,stroke:#333,stroke-width:0.3px
```
	
# Component Runtime Execution Requirements

## Initialization and Startup

The caller will initialize the TVSettings HAL APIs with picture quality modes for specific platforms and initiates communication with Picture Quality drivers.

 1. The specification of the TV Picure configuration will be defined in a config file([allmodes_template.conf](../../configs/allmodes_template.conf)) which decides supported formats, picture modes, dimming modes, dvModes, HDRModes, HLGModes, resolution etc.
 2. TV Settings HAL gets initialized by tvInit() API, which should initialize the parameters in the above config file aswell.

## Threading Model #TBC

TV Setting HAL is not required to be thread safe. 
There are no constraints on thread creation or signal handling. 

## Process Model

The interface is expected to support a single instantiation with a single process.

## Memory Model

The caller is responsible for allocating and cleaning up any memory used.

## Power Management Requirements

TV Settings HAL is not required to participate in power management.

## Asynchronous Notification Model

The TV Setting HAL has callback registered for VideoFormatChange, VideoResolutionChange, VideoFrameRateChange. On any update, the TV Setting HAL will notify it to the caller.

## Blocking calls

There are no blocking calls in TV Settings HAL.

## Internal Error Handling

All the TV Settings HAL APIs must return error synchronously as return argument. HAL is responsible to handle system errors internally(e.g. out of memory).

## Persistence Model

Every OEM vendor has to define the config file in OEM layer.
Config file should contain the supported formats, picture modes, dimming modes, dvModes, HDRModes, HLGModes, resolution etc.

# Nonfunctional requirements

Following non functional requirement must be supported by the TV Settings HAL component.

## Logging and debugging requirements

There is no Logging mechanism handled in TVSetting HAL. As of now printf() is used to to dump the TVSetting HAL logs.

## Memory and performance requirements

TV Settings HAL must not contribute to excessive memory and CPU utilization while configuring Picture Quality settings.

## Quality Control

TV Settings HAL implementation should perform static analysis, our preferred tool is Coverity.

- Have a zero-warning policy with regards to compiling. All warnings should be treated as error.
- Use of memory analysis tools like Valgrind are encouraged, to identify leaks/corruptions.
- HAL Tests will endeavour to create worst case scenarios to assist investigations

## Licensing

TV Settings HAL implementation is expected to get released under the Apache License 2.0. 

## Build Requirements

TV Settings HAL source code must be built by linking the shared library(libtvsettings-hal.so).
  
## Variability Management

Any changes in the APIs should be reviewed and approved by COMCAST.

## Platform or Product Customization

Product or platform specification requirements for a specific product can be handled in TV Settings HAL and modified in the config file.

# Interface API Documentation

API documentation will be provided.

## Theory of operation and key concepts

This interface handles various functionalities related to Picture Quality settings such as:

- Brightness
- Contrast
- Hue
- Saturation
- White Balance
- Sharpness
- Color Temperature
- Backlight 
- Aspect Ratio
- Dimming Modes

There are other platform specific Picture Quality settings that would be managed by this interface such as:

- CMS
- Dolby Vision
- HDR
- HLG

### Diagrams

#### Sequence Diagram

```mermaid
sequenceDiagram
Application ->> TV setting HAL:request
TV setting HAL ->> Driver:request
Driver ->> TV setting HAL:success/failure
TV setting HAL ->> Application:success/failure
```

#### State Diagram

```mermaid
stateDiagram-v2
    [*] --> Configured: Initialize Picture Quality params
    Configured --> Control: Set/get/reset PQ params
    Control --> Validate: Recieve response from driver
    Validate --> Configured
```
