#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

int open_chip(const char *chipname, struct gpiod_chip **chip) {
	*chip = gpiod_chip_open_by_name(chipname);
	if (!chip) {
                fprintf(stderr, "Open chip failed [chip=%s]\n", chipname);
                return 1;
        } else {
		return 0;
	}
}

int open_line(struct gpiod_chip *chip, const unsigned int pin, struct gpiod_line **line) {
	*line = gpiod_chip_get_line(chip, pin);
        if (!line) {
                fprintf(stderr, "Open pin failed [pin=%i]\n", pin);
                gpiod_chip_close(chip);
                return 1;
        } else {
		return 0;
	}
}

int request_output(struct gpiod_chip *chip, struct gpiod_line *line, const char *consumer) {
	if (gpiod_line_request_output(line, consumer, 0) == -1) {
                fprintf(stderr, "Requesting line as output failed [line address=%p]\n", line);
                gpiod_line_release(line);
                gpiod_chip_close(chip);
                return 1;
        } else {
		return 0;
	}
}

int set_value(struct gpiod_chip *chip, struct gpiod_line *line, unsigned int value) {
	if (gpiod_line_set_value(line, value)) {
        	fprintf(stderr, "Set line output failed [line address=%p, value=%i]\n", line, value);
                gpiod_line_release(line);
                gpiod_chip_close(chip);
                return 1;
        } else {
		return 0;
	}
}

int toggle_led(struct gpiod_chip *chip, struct gpiod_line *line) {
	// turn on for 1 microsecond
	struct timespec tim, tim2;
   	tim.tv_sec = 0;
   	tim.tv_nsec = 100000000L;

	if (set_value(chip, line, 1))
		return 1;
	if (nanosleep(&tim, &tim2) < 0) {
		fprintf(stderr, "Nanosleep system call failed\n");
		gpiod_line_release(line);
                gpiod_chip_close(chip);
		return 1;
	}
	if (set_value(chip, line, 0))
                return 1;
	return 0;
}



int main() {
	const char *chipname = "gpiochip0";
	const unsigned int pin_red = 18;
	const unsigned int pin_yellow = 23;
	const unsigned int pin_green = 24;
	const char *consumer = "Consumer";
	unsigned int val = 0;
	struct gpiod_chip *chip;
	struct gpiod_line *line_red;
	struct gpiod_line *line_yellow;
	struct gpiod_line *line_green;

	if (open_chip(chipname, &chip))
		return -1;

	if (open_line(chip, pin_red, &line_red))
		return -1;

	if (open_line(chip, pin_yellow, &line_yellow))
		return -1;

	if (open_line(chip, pin_green, &line_green))
		return -1;

	if (request_output(chip, line_red, consumer))
		return -1;

	if (request_output(chip, line_yellow, consumer))
                return -1;

	if (request_output(chip, line_green, consumer))
                return -1;

	// Blink 10 times
	for (int i = 0; i < 10; i++) {
		toggle_led(chip, line_red);
		toggle_led(chip, line_yellow);
		toggle_led(chip, line_green);
	}

	gpiod_line_release(line_red);
        gpiod_line_release(line_yellow);
	gpiod_line_release(line_green);
	gpiod_chip_close(chip);
	return 0;


}
