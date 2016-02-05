#define DEVICE_ID		0x12

//Communication to DAQ Board definitions
#define RECORD_START		0x01
#define RECORD_END			0x02
#define SET_CMOS_SETTINGS	0x03
     //For setting MS FPS Bit 4 defines a FPS command
#define FPS5				0x11
#define FPS10				0x12
#define	FPS15				0x13
#define	FPS20				0x14
#define FPS30				0x15
#define	FPS60				0x16


//Mask for External Trigger GPIO Check
#define TRIG_RECORD_EXT		0x02



//Probably can delete everything below 

// =========== USART Comm =======================
#define GET_ID			0x01
#define GET_CURRENT0	0x30
#define GET_CURRENT1	0x31

#define SET_CURRENT		0x10
#define OSC_ON0			0x21
#define OSC_ON1			0x22
#define OSC_OFF			0x20

//============ USART ============================
#define USART_PORT		PORTD
#define USART_DDR		DDRD
#define TXD				PD1
#define RXD				PD0
#define MYUBRR			12   //for 57600bits/s

// =========== SPI ==============================
#define SPI_PORT		PORTB
#define SPI_DDR			DDRB
#define MOSI			PB3
#define MISO			PB4
#define SCK				PB5
#define SS				PB2

// =========== OSC ==============================
#define OSC_PORT		PORTD
#define OSC_DDR			DDRD
#define OSC0			PD2	//26.6MHz
#define	OSC1			PD3	

// ========== DAC ===============================
#define DAC_CTRL_PORT	PORTB
#define DAC_CTRL_DDR	DDRB
#define DAC_SHDN		PB2
#define DAC_LDAC		PB1
#define DAC_CS			PB0

#define AnB				15
#define BUF				14
#define GAn				13
#define SHDNn			12
// ========= GPIO ===============================
#define GPIO_PORT		PORTC
#define GPIO_DDR		DDRC