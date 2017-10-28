/*
void screen1()
{
//	char i;
	//unsigned char *p_time;
	
	//reset to line 1 of LCD, position 0
	//cmd(LCD_HOME);
	
	//get the time
	//p_time = rtc_get_time();
	
	//--------------print the time-------------
	/*
	for(i = 2; i >= 0; i++)
	{
		print_o(*(p_time+i));
		write_int(*(p_time+i));
		write_char(':');
	}
	
	//hours
	print_o(*(p_time+2));
	write_int(*(p_time+2));
	write_char(':');
	
	//minutes
	print_o(*(p_time+1));
	write_int(*(p_time+1));	
	write_char(':');
	
	//seconds
	print_o(*(p_time));
	write_int(*(p_time));
	write_char(' ');
	
	//readDHT11();
	//print_temp();
	
	//print temp
	write_int(bmpTemp/100);
	write_char('.');
	write_int(bmpTemp % 100);
	//write temperature symbol *c
	write_char(0);
	write_char(' ');
	
	cmd(LCD_LINE_2);
	
	//day
	print_o(*(p_time+4));
	write_int(*(p_time+4));
	write_char('/');
	//month
	print_o(*(p_time+5));
	write_int(*(p_time+5));
	write_char('/');
	//year
	print_o(*(p_time+6));
	write_int(*(p_time+6));
	
	
	write_char(' ');

	write_int(bmpPressure/1000);
	write_int((bmpPressure % 1000) / 100);
	write_char('.');
	write_int(bmpPressure % 100);

	/*
	matrixSend(0x01, bcdToDec(*(p_time)));
	
	matrixSend(0x02, bcdToDec(*(p_time+1)));
	matrixSend(0x03, bcdToDec(*(p_time+2)));
	
	
	//seconds
	matrixSend(0x01, (*(p_time) & 0x0F));
	serial_convert((*(p_time) & 0x0F));

	matrixSend(0x02, (*(p_time)/10 & 0x0F));
	serial_convert((*(p_time)/10 & 0x0F));
	serial_send(' ');
	
	//minutes
	matrixSend(0x03, (*(p_time+1) & 0x0F));
	serial_convert((*(p_time+1) & 0x0F));
	
	matrixSend(0x04, (*(p_time+1)/10 & 0x0F));
	serial_convert((*(p_time+1)/10 & 0x0F));
	serial_send(' ');
	
	//hours
	matrixSend(0x05, (*(p_time+2) & 0x0F));
	serial_convert((*(p_time+2) & 0x0F));
	
	matrixSend(0x06, (*(p_time+2)/10 & 0x0F));
	serial_convert((*(p_time+2)/10 & 0x0F));
	serial_send(' ');
	
	serial_send('\r');
	serial_send('\n');
	
		/*
		maxTest(0x04, (*(p_time)+4));
		maxTest(0x05, (*(p_time)+5));
		maxTest(0x06, (*(p_time)+6));
		maxTest(0x07, (*(p_time)+3));
	
	//cmd(LCD_LINE_2);
	
//	print_pressure();
}

void serial()
{
	Sprint_o(*(p_time+2));
	serial_convert(*(p_time+2));
	serial_send(':');
	
	//minutes
	Sprint_o(*(p_time+1));
	serial_convert(*(p_time+1));	
	serial_send(':');
	
	//seconds
	Sprint_o(*(p_time));
	serial_convert(*(p_time));
	serial_send(' ');
	
	//readDHT11();
	//print_temp();
	
	//print temp
	serial_convert(bmpTemp/100);
	serial_send('.');
	serial_convert(bmpTemp % 100);
	//write temperature symbol *c
	serial_send('*');
	serial_send('C');
	serial_send(' ');
	
	//day
	Sprint_o(*(p_time+4));
	serial_convert(*(p_time+4));
	serial_send('/');
	//month
	Sprint_o(*(p_time+5));
	serial_convert(*(p_time+5));
	serial_send('/');
	//year
	Sprint_o(*(p_time+6));
	serial_convert(*(p_time+6));
	
	serial_send(' ');
	
	serial_convert(bmpPressure/1000);
	serial_convert((bmpPressure % 1000) / 100);
	serial_send('.');
	serial_convert(bmpPressure % 100);
	
	serial_send('\r');
	serial_send('\n');
}
*/
