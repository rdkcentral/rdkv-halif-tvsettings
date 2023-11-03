
# TV Settings HAL Documentation

## Version History

| Date(DD/MM/YY) | Comment | Version |
| --- | --- | --- |
| 20/03/23 | Edited | 1.0.1 |
| 16/11/22 | First Release | 1.0.0 |

## Table of Contents

- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Description](#description)
- [Component Runtime Execution Requirements](#component-runtime-execution-requirements)
  - [Initialization and Startup](#initialization-and-startup)
  - [Threading Model](#threading-model)
  - [Process Model](#process-model)
  - [Memory Model](#memory-model)
  - [Power Management Requirements](#power-management-requirements)
  - [Asynchronous Notification Model](#asynchronous-notification-model)
  - [Blocking calls](#blocking-calls)
  - [Internal Error Handling](#internal-error-handling)
  - [Persistence Model](#persistence-model)
- [Non-functional requirements](#non-functional-requirements)
  - [Logging and debugging requirements](#logging-and-debugging-requirements)
  - [Memory and performance requirements](#memory-and-performance-requirements)
  - [Quality Control](#quality-control)
  - [Licensing](#licensing)
  - [Build Requirements](#build-requirements)
  - [Variability Management](#variability-management)
  - [Platform or Product Customization](#platform-or-product-customization)
- [Interface API Documentation](#interface-api-documentation)
  - [Theory of operation and key concepts](#theory-of-operation-and-key-concepts)
  - [Diagrams](#diagrams)

## Acronyms, Terms and Abbreviations

- `CPU` - Central Processing Unit
- `HAL` - Hardware Abstraction layer
- `PQ`  - Picture Quality
- `SOC` - System on chip
- `OEM` - Original Equipment Manufacturer
- `ALS` - Auto Light Sensor
- `API` - Application Programming Interface

## Description

TV Settings `HAL` is an interface which provides `APIs` to modify/control the picture quality parameters, dimming modes and auto backlight modes.

```mermaid
%%{ init : { "theme" : "forest", "flowchart" : { "curve" : "linear" }}}%%
flowchart TD
Caller <--> x[TV Setting HAL] 
x[TV Setting HAL] <--> y[Video/Picture Quality Driver]
style Caller fill:#99CCFF,stroke:#333,stroke-width:0.3px
style y fill:#fc9,stroke:#333,stroke-width:0.3px
style x fill:#9f9,stroke:#333,stroke-width:0.3px
```
	
## Component Runtime Execution Requirements

### Initialization and Startup

The caller should initialize the `APIs` with picture quality modes for specific platforms and initiates communication with picture quality drivers.

 1. The specification of the TV picure configuration will be defined in a config file ([allmodes_template.conf](../../config/allmodes_template.conf "allmodes_template.conf")) which decides supported formats, picture modes, dimming modes, dvModes, HDRModes, HLGModes, resolution etc.
 2. Caller should initialize by calling `tvInit()` which should initialize the parameters in the above config file as well.

### Threading Model

This interface is not required to be thread safe. 
There are no constraints on thread creation or signal handling. 

### Process Model

This interface is expected to support a single instantiation with a single process.

### Memory Model

The caller is responsible for allocating and cleaning up any memory used.

### Power Management Requirements

This interface is not required to participate in power management.

### Asynchronous Notification Model

This interface requires callback notification registration for VideoFormatChange, VideoResolutionChange, VideoFrameRateChange, VideoContentChange. The caller must return the callback context as fast as possible and will not block.

### Blocking calls

This interface is required to have no blocking calls.

### Internal Error Handling

All `APIs` must return error synchronously as return argument.

### Persistence Model

Each vendor needs to define their own config file which is expected to be stored in rootfs and this must be a readonly.
Config file should contain the supported formats, picture modes, dimming modes, dvModes, HDRModes, HLGModes, resolution etc.

## Non-functional requirements

Following non-functional requirement must be supported by the TV Settings `HAL` component:

### Logging and debugging requirements

This interface is required to support DEBUG, INFO and ERROR messages. DEBUG is required to be disabled by default and enabled when needed.

### Memory and performance requirements

This interface is required  to not cause excessive memory and CPU utilization.

### Quality Control

- This interface is required to perform static analysis, our preferred tool is Coverity.
- Have a zero-warning policy with regards to compiling. All warnings should be treated as errors.
- Use of memory analysis tools like Valgrind are encouraged to identify leaks/corruptions.
- `HAL` Tests will endeavour to create worst case scenarios to assist investigations.
- Copyright validation is required to be performed, e.g.: `Black duck`, `FossID`.
- Improvements by any party to the testing suite are required to be fed back.

### Licensing

This interface is expected to get released under the Apache License 2.0.

### Build Requirements

TV Settings `HAL` source code must build into a shared library and must be named as `libtvsettings-hal.so`.
  
### Variability Management

Any changes in the `APIs` should be reviewed and approved by component architects.

### Platform or Product Customization

Product or platform specification requirements will be handled in vendor specific config file.

## Interface API Documentation

`API` documentation will be provided by Doxygen which will be generated from the header file(s).

### Theory of operation and key concepts

This interface handles various functionalities/requests related to Picture Quality settings :

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
- Notify Video Format Change
- Notify Video Resolution Change
- Notify Video FrameRate Change
- Notify Video Content Change

There are other platform specific Picture Quality settings that can be managed by this interface :

- CMS
- Dolby Vision
- HDR
- HLG

### Diagrams

#### Operational Call Diagram

```mermaid
sequenceDiagram
Caller ->> TV setting HAL: tvInit()
TV setting HAL ->> Caller:success
Caller ->> TV setting HAL: request
TV setting HAL ->> SoC Driver: request
SoC Driver ->> TV setting HAL:success/failure
TV setting HAL ->> Caller:success/failure
TV setting HAL ->> TV setting HAL:Register callback
SoC Driver ->> TV setting HAL:Notify on video format/framerate/resolution change
TV setting HAL ->> Caller:Notify on video format/framerate/resolution change
```

#### Functional Diagram

```mermaid
stateDiagram-v2
    [*] --> ClosedState
    ClosedState --> OpenState: tvInit()-Initialize Picture Quality params
    OpenState --> ControlState: Set/Get PQ params
    ControlState --> Validate: Recieve success/failure response from driver
    Validate --> OpenState
    OpenState --> MonitorState: Watch for events
    MonitorState --> NotifyState: Notify events
    NotifyState --> MonitorState
```
