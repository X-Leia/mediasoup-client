/**
 * This file is part of mediasoup_client project.
 * Author:    Jackie Ou
 * Created:   2021-11-01
 **/

#include "string_utils.h"
#include <random>
#include <time.h>
#include <chrono>
#include "logger/spd_logger.h"

namespace vi {
	// Helper method to create random identifiers (e.g., transaction)
	 std::string StringUtils::randomString(int32_t len) {
		std::string charSet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
		std::string randomString;

		std::default_random_engine engine((int64_t)std::chrono::steady_clock::now().time_since_epoch().count());
		std::uniform_int_distribution<int> dist(0, charSet.length() - 1);

		for (int32_t i = 0; i < len; ++i) {
			int32_t randomPoz = dist(engine);
			//DLOG("--> pos = {}", randomPoz);
			randomString += charSet.substr(randomPoz, 1);
		}
		return randomString;
	}
}