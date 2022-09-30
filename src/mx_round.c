int mx_round(double value) {
	return (value - (int)value < 0.5) ? (int) value : (int) value + 1;
}

