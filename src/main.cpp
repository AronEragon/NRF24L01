#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/adc.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>

#define LBLUE GPIOE, GPIO8
#define LRED GPIOE, GPIO9
#define LORANGE GPIOE, GPIO10
#define LGREEN GPIOE, GPIO11
#define LBLUE2 GPIOE, GPIO12
#define LRED2 GPIOE, GPIO13
#define LORANGE2 GPIOE, GPIO14
#define LGREEN2 GPIOE, GPIO15

#define LD4 GPIOE, GPIO8
#define LD3 GPIOE, GPIO9
#define LD5 GPIOE, GPIO10
#define LD7 GPIOE, GPIO11
#define LD9 GPIOE, GPIO12
#define LD10 GPIOE, GPIO13
#define LD8 GPIOE, GPIO14
#define LD6 GPIOE, GPIO15


void spi_setup1() {
    
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_SPI1);

    // Настройка пинов SPI1: SCK (PA5), MISO (PA6), MOSI (PA7)
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO5 | GPIO6 | GPIO7);
    gpio_set_af(GPIOA, GPIO_AF5, GPIO5 | GPIO6 | GPIO7); // Альтернативная функция AF5 для SPI1
    gpio_set_output_options(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, GPIO5 | GPIO6 | GPIO7);

    // Конфигурация SPI1
    spi_disable(SPI1);
    spi_set_slave_mode(SPI1);                  // Устанавливаем режим slave
    spi_set_baudrate_prescaler(SPI1, SPI_CR1_BR_FPCLK_DIV_64);
    spi_set_clock_polarity_0(SPI1);            // Полярность CLK = 0
    spi_set_clock_phase_0(SPI1);               // Фаза CLK = 0
    spi_set_data_size(SPI1, SPI_CR2_DS_8BIT);  // 8-битный размер данных
    spi_send_msb_first(SPI1);                  // Отправка старшего бита первым
    spi_enable_software_slave_management(SPI1);
    spi_set_nss_low(SPI1);
    spi_fifo_reception_threshold_8bit(SPI1);
    spi_enable(SPI1);                          // Включаем SPI1
}


static void spi_setup2(void)
{
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_SPI2);

    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO13| GPIO14 | GPIO15);
    gpio_set_af(GPIOB, GPIO_AF5, GPIO13| GPIO14 | GPIO15);
    gpio_set_output_options(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, GPIO13| GPIO14 | GPIO15);

    spi_disable(SPI2);
    spi_set_master_mode(SPI2);
    spi_set_baudrate_prescaler(SPI2, SPI_CR1_BR_FPCLK_DIV_64);
    spi_set_clock_polarity_0(SPI2);
    spi_set_clock_phase_0(SPI2);
    spi_set_data_size(SPI2, SPI_CR2_DS_8BIT);
    spi_send_msb_first(SPI2);
    spi_enable_software_slave_management(SPI2);
    spi_set_nss_high(SPI2);
    spi_fifo_reception_threshold_8bit(SPI2);
    spi_enable(SPI2);
}


#define LBLUE GPIOE, GPIO8
#define LRED GPIOE, GPIO9
#define LORANGE GPIOE, GPIO10
#define LGREEN GPIOE, GPIO11
#define LBLUE2 GPIOE, GPIO12
#define LRED2 GPIOE, GPIO13
#define LORANGE2 GPIOE, GPIO14
#define LGREEN2 GPIOE, GPIO15

#define LD4 GPIOE, GPIO8
#define LD3 GPIOE, GPIO9
#define LD5 GPIOE, GPIO10
#define LD7 GPIOE, GPIO11
#define LD9 GPIOE, GPIO12
#define LD10 GPIOE, GPIO13
#define LD8 GPIOE, GPIO14
#define LD6 GPIOE, GPIO15




static void gpio_setup(void)
{
    rcc_periph_clock_enable(RCC_GPIOE);
    gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
        GPIO8 | GPIO9 | GPIO10 | GPIO11 | GPIO12 | GPIO13 |
        GPIO14 | GPIO15);
}

static void clock_setup(void)
{
    rcc_clock_setup_hsi(&rcc_hsi_configs[RCC_CLOCK_HSI_64MHZ]);
}

int main(void)
{
    uint16_t temp;

    clock_setup();
    gpio_setup();
    spi_setup1();
    spi_setup2();

    while (1) {
        
		gpio_toggle(GPIOE, GPIO9); 
        
        // spi_send8(SPI2, 85); // Обновлено на SPI2
        temp = spi_read(SPI1);
  
        // spi_write(SPI2, temp);
        spi_send8(SPI2, temp);
        

        int i;
        for (i = 0; i < 80000; i++)    /* Wait a bit. */
            asm("nop");
    }

    return 0;
}
