# testVelocity2D

## Overview

Test TimedVelocity2D OutPort Component

## Description

TimedVelocity2D型のOutPortのデータを出力するコンポーネント

### Input and Output



### Algorithm etc



### Basic Information

|  |  |
----|---- 
| Module Name | testVelocity2D |
| Description | Test TimedVelocity2D OutPort Component |
| Version | 1.0.0 |
| Vendor | AIST |
| Category | Test |
| Comp. Type | STATIC |
| Act. Type | PERIODIC |
| Kind | DataFlowComponent |
| MAX Inst. | 1 |

### Activity definition

<table>
  <tr>
    <td rowspan="4">on_initialize</td>
    <td colspan="2">implemented</td>
    <tr>
      <td>Description</td>
      <td></td>
    </tr>
    <tr>
      <td>PreCondition</td>
      <td></td>
    </tr>
    <tr>
      <td>PostCondition</td>
      <td></td>
    </tr>
  </tr>
  <tr>
    <td>on_finalize</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>on_startup</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>on_shutdown</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>on_activated</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>on_deactivated</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td rowspan="4">on_execute</td>
    <td colspan="2">implemented</td>
    <tr>
      <td>Description</td>
      <td></td>
    </tr>
    <tr>
      <td>PreCondition</td>
      <td></td>
    </tr>
    <tr>
      <td>PostCondition</td>
      <td></td>
    </tr>
  </tr>
  <tr>
    <td>on_aborting</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>on_error</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>on_reset</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>on_state_update</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>on_rate_changed</td>
    <td colspan="2"></td>
  </tr>
</table>

### InPorts definition


### OutPorts definition

#### out

コンフィギュレーションパラメータで設定した速度をTimedVelocity2D型で出力する。

<table>
  <tr>
    <td>DataType</td>
    <td>RTC::TimedVelocity2D</td>
    <td>RTC::TimedVelocity2D</td>
  </tr>
  <tr>
    <td>IDL file</td>
    <td colspan="2">ExtendedDataTypes.idl</td>
  </tr>
  <tr>
    <td>Number of Data</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Semantics</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Unit</td>
    <td colspan="2">m/s, rad/s</td>
  </tr>
  <tr>
    <td>Occirrence frecency Period</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Operational frecency Period</td>
    <td colspan="2"></td>
  </tr>
</table>


### Service Port definition


### Configuration definition

#### speed_x

outから出力するX軸方向の直進速度を設定する。


<table>
  <tr>
    <td>DataType</td>
    <td colspan="2">double</td>
  </tr>
  <tr>
    <td>DefaultValue</td>
    <td>0.0</td>
    <td>0.0</td>
  </tr>
  <tr>
    <td>Unit</td>
    <td>m/s</td>
    <td>m/s</td>
  </tr>
  <tr>
    <td>Widget</td>
    <td colspan="2">slider</td>
  </tr>
  <tr>
    <td>Step</td>
    <td colspan="2">0.1</td>
  </tr>
  <tr>
    <td>Constraint</td>
    <td>-10.0<x<10.0</td>
    <td>-10.0<x<10.0</td>
  </tr>
  <tr>
    <td>Range</td>
    <td colspan="2"></td>
  </tr>
</table>

#### speed_y

outから出力するY軸方向の直進速度を設定する。


<table>
  <tr>
    <td>DataType</td>
    <td colspan="2">double</td>
  </tr>
  <tr>
    <td>DefaultValue</td>
    <td>0.0</td>
    <td>0.0</td>
  </tr>
  <tr>
    <td>Unit</td>
    <td>m/s</td>
    <td>m/s</td>
  </tr>
  <tr>
    <td>Widget</td>
    <td colspan="2">slider</td>
  </tr>
  <tr>
    <td>Step</td>
    <td colspan="2">0.1</td>
  </tr>
  <tr>
    <td>Constraint</td>
    <td>-10.0<x<10.0</td>
    <td>-10.0<x<10.0</td>
  </tr>
  <tr>
    <td>Range</td>
    <td colspan="2"></td>
  </tr>
</table>

#### speed_r

outから出力する回転速度を設定する。


<table>
  <tr>
    <td>DataType</td>
    <td colspan="2">double</td>
  </tr>
  <tr>
    <td>DefaultValue</td>
    <td>0.0</td>
    <td>0.0</td>
  </tr>
  <tr>
    <td>Unit</td>
    <td>rad/s</td>
    <td>rad/s</td>
  </tr>
  <tr>
    <td>Widget</td>
    <td colspan="2">slider</td>
  </tr>
  <tr>
    <td>Step</td>
    <td colspan="2">0.1</td>
  </tr>
  <tr>
    <td>Constraint</td>
    <td>-3.0<x<3.0</td>
    <td>-3.0<x<3.0</td>
  </tr>
  <tr>
    <td>Range</td>
    <td colspan="2"></td>
  </tr>
</table>


## Demo

## Requirement

## Setup

### Windows

### Ubuntu

## Usage

## Running the tests

## LICENCE

LGPL


## References




## Author


