#include "usart.h"

void USART_Init()
{
	UBRR0H = (uint8_t) (MYUBRR>>8);				// Ajuste da transmissão em 9600 bps
	UBRR0L = (uint8_t)(MYUBRR);
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);				// Habilita transmissão e recepção
	UCSR0C = (3<<UCSZ00);						// Modo assincrono, 8 bits, 1 stop, sem paridade
}
//-------------------------------------------------------------------------------------------------------
void USART_Transmit(unsigned char data)
{
	while(!(UCSR0A & (1<<UDRE0)));				// Espera o dado ser enviado
	UDR0 = data;								// Envia o dado pela porta serial
}

//-------------------------------------------------------------------------------------------------------
unsigned char USART_Receive()
{
	while(!(UCSR0A & (1<<RXC0)));				// Espera o dado ser recebido
	return UDR0;
}

//-------------------------------------------------------------------------------------------------------
void USART_StrTx(const char* ptr)
{
	while(*ptr != '\0')
	{
		USART_Transmit(*ptr);
		ptr++;
	}
}
//-------------------------------------------------------------------------------------------------------
void USART_rxIE()
{
	UCSR0B |= (1 << RXCIE0 );
}

/**
 * Vetor de Interrupção USART RX
 */
char usart_rx_buffer[100];
volatile uint16_t indice = 0;
volatile uint8_t frame_status = 0;

ISR( USART_RX_vect )
{
	unsigned char data;

	/**
	 *  Verifica se houve erro durante a recepção serial;
	 *  FE0 = Frame Error;
	 *  DOR0 = Data OverRun;
	 *  UPE0 = USART Parity Error;
	 */
	 
	 data = UDR0;
	
	if((UCSR0A & ((1 << FE0) | (1 << DOR0) | (1 << UPE0))) == 0)
	{

		/**
		 * Buffer cheio? Caso sim, reinicia indice
		 */		
		if(indice >= sizeof(usart_rx_buffer))
		{
			indice = 0;
		}
		
		/**
		 * Caractere indicador de fim de frame;
		 */
		if( data == '\n' )
		{
			usart_rx_buffer[indice] = '\0'; 
			frame_status = 1; 
			indice = 0;
		} 
		/* Armazena os bytes recebidos no buffer */
		else {
			usart_rx_buffer[indice++] = data; 
		}
	
	}
}

void read_usart_rx_buffer(char *temp_usart_rx_buffer){
	temp_usart_rx_buffer = usart_rx_buffer;
}



