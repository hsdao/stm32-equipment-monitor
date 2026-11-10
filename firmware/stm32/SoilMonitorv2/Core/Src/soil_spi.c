#include "soil_spi.h"

#define SOIL_READ_INTERVAL_MS 1000U

static SPI_HandleTypeDef *soilSpiHandle = NULL;

/* Known bytes for the MOSI-to-MISO loopback test */
static uint8_t spiTx[4] = {0x00, 0xFA, 0x03, 0x2A};
static uint8_t soilRx[4] = {0};

static volatile uint8_t spiDone = 0;
static volatile uint8_t spiError = 0;

static uint8_t spiBusy = 0;
static uint32_t lastSoilRead = 0;

static SoilData_t soilData = {0};


/* Call once after MX_SPI2_Init(), before starting transfers. */
void SoilSPI_Init(SPI_HandleTypeDef *hspi)
{
    soilSpiHandle = hspi;

    spiDone = 0;
    spiError = 0;
    spiBusy = 0;

    lastSoilRead = HAL_GetTick();

    soilData.temperature = 0.0f;
    soilData.moisture = 0.0f;
    soilData.valid = 0;

    for (uint32_t i = 0; i < sizeof(soilRx); i++)
    {
        soilRx[i] = 0;
    }
}


/* Call repeatedly from the main loop. */
void SoilSPI_Process(void)
{
    if (soilSpiHandle == NULL)
    {
        return;
    }

    /* Handle an error reported by the interrupt callback. */
    if (spiError)
    {
        spiError = 0;
        spiDone = 0;

        soilData.valid = 0;
        spiBusy = 0;
    }

    /* Handle a completed transfer. */
    if (spiDone)
    {
        spiDone = 0;

        uint8_t matches = 1;

        for (uint32_t i = 0; i < sizeof(spiTx); i++)
        {
            if (soilRx[i] != spiTx[i])
            {
                matches = 0;
                break;
            }
        }

        soilData.valid = 0;

        if (matches)
        {
            uint16_t temperatureRaw =
                ((uint16_t)soilRx[0] << 8) | soilRx[1];

            uint16_t moistureRaw =
                ((uint16_t)soilRx[2] << 8) | soilRx[3];

            soilData.temperature = temperatureRaw / 10.0f;
            soilData.moisture = moistureRaw / 10.0f;
            soilData.valid = 1;
        }

        /* Release the buffer only after processing it. */
        spiBusy = 0;
    }

    /* Start a new transfer when the interval has elapsed. */
    uint32_t now = HAL_GetTick();

    if ((spiBusy == 0) &&
        ((uint32_t)(now - lastSoilRead) >= SOIL_READ_INTERVAL_MS))
    {
        lastSoilRead = now;

        spiDone = 0;
        spiError = 0;
        spiBusy = 1;

        HAL_StatusTypeDef status = HAL_SPI_TransmitReceive_IT(
            soilSpiHandle,
            spiTx,
            soilRx,
            sizeof(spiTx)
        );

        if (status != HAL_OK)
        {
            soilData.valid = 0;
            spiBusy = 0;
        }
    }
}


/* Return a copy of the latest reading. Call from the main loop. */
SoilData_t SoilSPI_GetData(void)
{
    return soilData;
}


/* HAL calls this when transmission and reception finish. */
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
    if ((soilSpiHandle != NULL) && (hspi == soilSpiHandle))
    {
        spiDone = 1;
    }
}


/* HAL calls this when it reports a transfer error. */
void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
    if ((soilSpiHandle != NULL) && (hspi == soilSpiHandle))
    {
        spiError = 1;
    }
}
