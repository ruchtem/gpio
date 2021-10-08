#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>


int main() {

	const char *chipname = "gpiochip0";
	const unsigned int pin = 18;
	const char *consumer = "Consumer";
	unsigned int val = 0;
	struct gpiod_chip *chip;
	struct gpiod_line *line;

	chip = gpiod_chip_open_by_name(chipname);
	if (!chip) {
		fprintf(stderr, "Open chip failed\n");
		return 1;
	}

	line = gpiod_chip_get_line(chip, pin);
	if (!line) {
		fprintf(stderr, "Open pin failed [pin=%i]\n", pin);
		gpiod_chip_close(chip);
		return 1;
	}

	//int success = gpiod_line_request_output(line, consumer, 0);
	if (gpiod_line_request_output(line, consumer, 0) == -1) {
		fprintf(stderr, "Requesting pin as output failed [pin=%i]\n", pin);
		gpiod_line_release(line);
                gpiod_chip_close(chip);
		return 1;
	}

	// Blink 10 times
	for (int i = 0; i < 5; i++) {
		if (gpiod_line_set_value(line, val)) {
			fprintf(stderr, "Set line output failed [pin=%i, value=%i]\n", pin, val);
			gpiod_line_release(line);
                	gpiod_chip_close(chip);
			return 1;
		}
		printf("Output set [pin=%u, value=%u]\n", val, pin);
		sleep(1);
		val = !val;
	}
	return 0;


}
