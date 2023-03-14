
# TV Settings HAL Documentation

## Version History

| Date | Author | Comment | Version |
| --- | --------- | --- | --- |
| 16/11/22 | Aishwariya Bhaskar | First Release | 1.0.0 |
| 13/03/23 | Review Team | Edited | 1.0.2 |

## Acronyms

1. CPU - Central Processing Unit
2. HAL - Hardware Abstraction layer
3. PQ - Picture Quality
4. SOC - System on chip
5. OEM - Original Equipment Manufacturer
6. ALS - Auto Light Sensor
7. CS - Control Setting

## Description

TV Settings HAL is an abstract layer, which provides APIs to Modify/Control the Picture quality parameters, dimming modes and auto backlight modes.

![TV Settings HAL diagram](images/tv_settings_hal_architecture.PNG)
	
# Component Runtime Execution Requirements

Once the application is activated, it initialize the TVSettings HAL APIS with picture quality modes for specific platforms and initiates communication with Picture Quality drivers.
SOC is responsible for handling the PQ settings at the end device as per the request from application via TV Settings HAL.

## Initialization and Startup

TvSettings HAL API will be initialized by ControlSettings Thunder plugin.
 1. TV Settings HAL initialized by Control Setting plugin via tvInit(). 
 2. The TV Settings HAL get/set methods which will be used by Control Setting plugin to set/get/reset induvidual PQ params.
 3. The file /etc/tv/allmodes.conf decides the supported formats, picture modes, dimming modes,dvModes,HDRModes,HLGModes, resolution etc., 
 4. ALS thread using tvsettings-hal to setBacklight() based on room light level.
 5. Other Picture Quality parameters such as Brightness, Contrast, Hue, ColorTemp, RGB Gain values etc., for different Picture Quality modes can be configured using the TV Setting HAL get/set API's. 
 6. TV Settings HAL instance can be terminated using tvTerm().

## Threading Model

TV Setting HAL is not required to be thread safe, implementation is vendor specific.

## Process Model

The interface is expected to support a single instantiation with a single process.

## Memory Model

The application is responsible to allocate, own the memory and clean up.

## Power Management Requirements

TV Settings HAL does participate in power management. It will cooperate with the Picture Quality Video Drivers for adjusting the Soc Picture Quality settings according to the power mode set.

## Asynchronous Notification Model

The Tv Setting HAL has callback registered for VideoFormatChange, VideoResolutionChange, VideoFrameRateChange. On any update the TV Setting HAL will notify it to the application through Control Setting Thunder Plugin.

## Blocking calls

There are no blocking calls in TV Settings HAL

## Internal Error Handling

All the TV Settings HAL API must return error synchronously as return argument. HAL is responsible to handle system errors internally(e.g. out of memory).

## Persistence Model

Every OEM vendor has to define the tvsettings.ini file name and allmodes.conf file name in OEM layer.
allmodes.conf contains supported pqmodes/formats etc.
TV Settings HAL will initialize with the parameters present in tvsettings.ini file.


# Nonfunctional requirements

Following non functional requirement must be supported by the TV Settings HAL component.

## Logging and debugging requirements

There is no Logging mechanism handled in TVSetting HAL. As of now inbuild C library output function is used to to dump the TVSetting HAL logs.

## Memory and performance requirements

TV Settings HAL must not contribute to excessive memory and CPU utilization while configuring Picture Quality settings.

## Quality Control

TVSettings HAL must pass coverity scan verification periodically without any issue.
Use memory analysis tools like Valgrind to identify memory leaks/corruption introduced by HAL and underneath SOC software. 

## Licensing

TV Settings HAL implementation is expected to get released under the Apache License 2.0. 

## Build Requirements

TV Settings HAL source code must be build under Linux Yocto environment and must be delivered as a shared library.
  
## Variability Management

Any changes in API must be implemented by all SOC vendor and RDK generic code will be compatible with specific version of TV Settings HAL software.

## Platform or Product Customization

Product or platform specific requirements can be handled in TV Settings HAL API and the Specifications for respective product can be modified in config file.

# Interface API Documentation

The application will allocate and own the memory and is responsible for clean up.

## Theory of operation and key concepts

- The TV Settings HAL acts as interface between the TV ControlSettings Thunder Plugin and Picture Quality drivers for handling various functionalities related to Picture Quality settings such as Brightness, Contrast, Hue, Saturation, Luminence, White Balance, Sharpness, Color Temperature, Backlight, Aspect Ratio etc., 
- The setting chage request using remote is sent to application and it navigates as a curl request to Control Setting Thunder plugin which then extracts the response and sends to TV Settings HAL.
- TThis HAL will then sends the corresponding request to driver to perform the necessary operation

### UML Diagrams

#### Sequence Diagram

![TV Settings HAL Init Sequence diagram](images/InitSequence.png)
![TV Settings HAL Set Sequence diagram](images/SetSequence.png)
![TV Settings HAL Get Sequence diagram](images/GetSequence.png)
![TV Settings HAL Reset Sequence diagram](images/ResetSequence.png)

#### State Diagram

![TV Settings HAL State Diagram](images/state_diagram.PNG)
