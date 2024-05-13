#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include "bluetooth_infra.h"
#include "current_time_service.h"

LOG_MODULE_REGISTER(ZephyrWatch_Main, LOG_LEVEL_INF);


int main() {
	int err = enable_bluetooth_and_start_advertisement();
	if (err) {
		LOG_ERR("Failed to enable Bluetooth and start advertisement (err %d)", err);
		return err;
	}

	for (int i = 0; i < 15; i++) {
		k_sleep(K_SECONDS(2));

		struct current_time time = get_current_time();
		LOG_INF("Current time: %d-%d-%d %d:%d:%d",
			time.year, time.month, time.day,
			time.hours, time.minutes, time.seconds);
	}

	err = disable_bluetooth_and_stop_advertisement();
	if (err) {
		LOG_ERR("Failed to disable Bluetooth and stop advertisement (err %d)", err);
		return err;
	}

	return 0;
}
