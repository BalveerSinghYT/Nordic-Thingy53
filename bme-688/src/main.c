#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/sys/printk.h>

int main(void)
{
    const struct device *dev = DEVICE_DT_GET_ANY(bosch_bme680);

    if (!device_is_ready(dev)) {
        printk("BME688 not ready\n");
        return 0;
    }

    struct sensor_value temp, hum, press;

    while (1) {

        // 1. Fetch from hardware (I2C read)
        sensor_sample_fetch(dev);

        // 2. Get values
        sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &temp);
        sensor_channel_get(dev, SENSOR_CHAN_HUMIDITY, &hum);
        sensor_channel_get(dev, SENSOR_CHAN_PRESS, &press);

        // 3. Print
        printk("Temp: %d.%06d C\n", temp.val1, temp.val2);
        printk("Humidity: %d.%06d %%\n", hum.val1, hum.val2);
        printk("Pressure: %d.%06d kPa\n\n", press.val1, press.val2);

        k_sleep(K_SECONDS(2));
    }
}