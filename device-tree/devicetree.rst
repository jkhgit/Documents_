Device-tree format
==================

kernel/arch/{ARCH}/boot/dts/vendors/target.dts

.. code-block:: C

  /dts-v1/;

  / {
        node1 {
            a-string-property = "A string";
            a-string-list-property = "first string", "second string";
            a-byte-data-property = [01 23 34 56];

            child-node1 {
                first-child-property;
                second-child-property = <1>;
                a-string-property = "Hello, world";
                ...
            };

            child-node2 {
                ...
            };
        };

        node2 {
            an-empty-property;
            a-cell-property = <1 2 3 4>; /* each number (cell) is a uint32 */

            child-node1 {
            };
        };
    };

Parameters
==================

Compatible
------------------

kernel/arch/{ARCH}/boot/dts/vendors/target.dtsi

.. code-block:: C

  label@address {
      ...
      compatible = "vendor,driver";
      ...
  };


kernel/drivers/../../someting.c

.. code-block:: C

  ...

  static const struct spi_device_id spidev_spi_ids[] = {
      ...
      {.name = "driver"}
      {},
  }

  ...

  static const struct of_device_id dt_dev_ids[] {
      ...
      {.compatible = "SoC,driver"}
      {},
  }

  ...

* compatibles is just priority
compatible = "SoC, driver";
compatible = "SoC1, driver1", "SoC2, driver2";

Cpu
------------------

kernel/arch/{ARCH}/boot/dts/vendors/target.dtsi

.. code-block:: C

  /dts-v1/;

  / {
        compatible = "acme,coyotes-revenge";

        cpus {

            #address-cells = <2>;
            #size-cells = <0>;

            cpu0: cpu@0 {
                ...
                compatible = "arm,coretex-a9"; // menufacturer,model
                ...
            };

            cpu1: cpu@1 {
                ...
                compatible = "arm,coretex-a9"; // menufacturer,model
                ...
            };

            ...

        };
    };

Pinctrl
------------------

*pinctrl-names*
[pinctrl-names: pinctrl state] (kernel/include/linux/pinctrl/pinctrl-state.h)

.. code-block:: C

  #define PINCTRL_STATE_DEFAULT "default"
  #define PINCTRL_STATE_DEFAULT "init"
  #define PINCTRL_STATE_DEFAULT "idle"
  #define PINCTRL_STATE_DEFAULT "sleep"

*pinctrl-n*

.. code-block:: C

  [pinctrl-state]
  label: node@address {
      ...
      pinctrl-names = "state 0", "state 1" ...;
      pinctrl-0 = <&pin0>; *pinmux select pin0 on state 0*
      pinctrl-1 = <&pin1>; *pinmux select pin1 on state 1*
      pinctrl-2 = <&pin2>; *pinmux select pin2 on state 2*
      pinctrl-3 = <&pin3>; *pinmux select pin3 on state 3*
      ...
      status = "okay";
  };

*cs-gpios
cs-gpios: chipselects (optianal for spi)*

pinctrl status and use Another state (default x)
e.g. use "high_speed" state in spi (rk3568)

drivers/spi/spi-rockchip.c

.. code-block:: C

  ...
    if (rs -> high_speed_state) {
        if (rs->freq > IO_DRIVER_4M_MAX_SCLK_OUT)
            pinctrl_select_state(rs->dev->pins->p,
                                 rs->dev->pins->high_speed_state);

        else
            pinctrl_select_state(rs->dev->pins->p,
                                 rs->dev->pins->default_state);
    }
  ...

*requests*
get/lookup/select/put # in struct foo_probe
  1. devm_pinctrl_get()
  2. pinctrl_lookup_state()
  3. pinctrl_select_state()
  4. devm_pinctrl_put() # release, but don't need it..

*ref. Documentation/driver-api/pinctrl.rst*
*check readl_relaxed in driver's config.*

Reg
------------------
reg = <addr1 length1 [addr2] [length2] [addr3] [length3]
... > reg's size is "Variable" -> need #address-cells & #size-cells

#address-cells: how many use cells for express addr (on 32bit = 1, 64bit = 2)
#size-cells: how many use cells for express size (on 32bit = 1, 64bit = 2), none size = 0

case 1: none length(size) devices on 32bit system
if 64 bit system, value = <2>

.. code-block:: C

  cpus {

      #address-cells = <1>; // on 32bit system if 64 bit system, value = <2>
      #size-cells = <0>; // none size. only have address

      cpu@0 {
          ...
          compatible = "arm,cortex-a9";
          reg = <0>; // reg in child node it can have 0 or 1
          ...
      };

      cpu@1 {
          ...
          compatible = "arm,cortex-a9";
          reg = <1>; // reg in child node it can have 0 or 1
          ...
      };

      ...

  };

case 2: device have length devices
if 64 bit system, value = <2>

.. code-block:: C

  /dts-v1/;

  / {
        #address-cells = <1>;
        #size-cells = <1>;

        serial@101f0000 {
            ...
            compatible = "arm,pl011";
            reg = <0x101f0000 0x1000>; // <addr, length>
            ...
        };

        serial@101f2000 {
            ...
            compatible = "arm,pl011";
            reg = <0x101f2000 0x1000>;
            ...
        };

        gpio@101f3000 { // gpio: 0x101f3000 ~ 0x101f3fff, 0x101f4000 ~ 0x101f400f
            ...
            compatible = "arm,pl061";
            reg = <0x101f3000 0x1000
                   0x101f4000 0x0010>;
            ...
        };

        interrupt-controller@10140000 {
            ...
            compatible = "arm,pl190";
            reg = <0x10140000 0x1000>;
            ...
        };

        spi@10115000 {
            ...
            compatible = "arm,pl022";
            reg = <0x10115000 0x1000>;
            ...
        };

        ...

    };

*check /proc/device-tree/*

case 3: external bus struct: they have select chip-line

.. code-block:: C

  external-bus {

      #address-cells = <2>;
      #size-cells = <1>;

      ethernet@0,0 { // node@{child},{parents}
          compatible = "smc,smc91c111";
          reg = <0 0 0x1000>; // <{chip-line} {offset} {length}>, offset: parents idx
          // address-cells(2): {chip-line}, {offset}
          // size-cells(1): {length}
      };

      i2c@1,0 {
          compatible = "acme,a1234-i2c-bus";
          reg = <1 0 0x1000>;
          ...

          rtc@58 {
              ...
              compatible = "maxim,ds1338";
              ...
          };
      };

      flash@2,0 {
          ...
          compatible = "samsung,k8f1315ebm", "cfi-flash";
          reg = <2 0 0x4000000>;
          ...
      };
  };

case4: Address Ranges

*ranges = <{child-addr} {parents-addr} {length}>*
*parent-addr: local addr based on root*
*length: data size*

*structure*
{parent}           {child}
root               external-bus
external-bus       ethernet, i2c, flash

::
  [/]
  L[external-bus]: offset 0 
  |  use cell:  /*2 cells*/   /*1 cell*/   /*1 cell*/
  L  ranges = <{child-addr} {parent-addr} {length}>
  L chip 1_[ethernet]@1,0
  |
  L chip 2_[i2c]@2,0
  |
  L chip 3_[flash]@3,0

.. code-block:: C

  /dts-v1/;

  / {
        ...
        compatible = "acme,coyotes-revenge";
        #address-cells = <1>; // external-bus 
        #size-cells = <1>; // external-bus
        ...

        external-bus {
            #address-cells = <2> // ethernet, i2c, flash
            #size-cells = <1>; // ethernet, i2c, flash

            ranges = <0 0  0x10100000   0x10000     /* Chipselect 1, (Ethernet) */
            1 0  0x10160000   0x10000      /* Chipselect 2, (i2c controller) */
            2 0  0x30000000   0x1000000>;    /* Chipselect 3, (NOR Flash) */

            ethernet@0,0 { // 0x10100000 ~ 0x10100fff
                ...
                compatible = "smc,smc91c111";
                reg = <0 0 0x1000>; // <{child} {offset} {length}>
                ...
            };

            i2c@1,0 { // 0x10160000 ~ 0x10160fff
                ...
                compatible = "acme,a1234-i2c-bus";
                #address-cells = <1>; // use cells for rtc@58 addr : 32 bit
                #size-cells = <0>; // use cells for rtc@58 : none memory size
                reg = <1 0 0x1000>; // <{child} {offset} {length}>

                rtc@58 {
                    compatible = "maxim,ds1338";
                    reg = <58>; // <{addr(child)}>
                };
            };

            flash@2,0 { // 0x30000000 ~ 0x33ffffff
                compatible = "samsung,k8f1315ebm", "cfi-flash";
                reg = <2 0 0x4000000>;
            };
        };
    };

*ranges info*
Chipselect 1 [chip 0 offset 0] 0x10100000 ~ 0x1010ffff*/
{child-addr} : {child} {offset} = 0 0
{parent-addr} : {external-bus's addr} 0x10100000
{length} : 0x10000

Chipselect 2 [chip 1 offset 0] 0x10160000 ~ 0x1016ffff
{child-addr} : {child} {offset} = 1 0
{parent-addr} : {external-bus's addr} 0x10160000
{length} : 0x10000

Chipselect 3 [chip 2 offset 0] 0x30000000 ~ 0x30ffffff
{child-addr} : {child} {offset} = 2 0
{parent-addr} : {external-bus's addr} 0x30000000
{length} : 0x1000000

Status
------------------
"okay" is activate code
"disabled" *The code that doesn't exist in the first place*

e.g.

.. code-block:: C

  status = "okay"
  status = "disabled"

*point use dtb/dtbo*

"disable" -> "okay" (o)

"okay" -> "disabled" (x)

Target.dts
------------------

.. code-block:: C

  #include "{target}.dtsi"
  
  &{label} {
    properties
    ...
  };

Target.dtsi
------------------

.. code-block:: C

  {label}: node {
      #adress-cells = <2>;
      #size-cells = <2>;

      {label}: {node} {
          ...
          compatible = "vendor,driver";
          reg = <{63:32} {31:0} {63:32} {31:0}>
          ...
      };
  };

*reg=<{63:32} {31:0} {63:32} {31:0}>

*check dt params
/proc/device-tree/..
