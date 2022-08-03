Add device module
=================

drivers/device/device.c

.. code-block:: C

  module_platform_driver(my_hw_driver);

include/linux/paltform_device.h

.. code-block:: C

  #define module_platform_driver(__platform_driver) \
      module_driver(__platform_driver, platform_driver_register,
                    paltform_driver_unregister)

include/linux/device.h

.. code-block:: C

  #define module_driver(__driver, __register, __unregister, ...) \
  static int __init __driver##_init(void) \
  { \
    return __register(&(__driver) , ##__VA_ARGS__); \
  } \
  module_init(__driver##_init); \
  static void __exit __driver##_exit(void) \
  { \
    __unregister(&(__driver) , ##__VA_ARGS__); \
  } \
  module_exit(__driver##_exit);
