
#ifndef USBTMC_APP_H
#define USBTMC_APP_H

void usbtmc_app_task_iter();

// 0=not query, 1=queried, 2=delay,set(MAV), 3=delay 4=ready?
// (to simulate delay)
enum  _states {
  QStart = 0,
  QDelayStart,
  QDelayRun,
  QDelayEnd,
  QSendResult
};


static volatile uint8_t status;
static unsigned int msgReqLen;
static volatile enum _states queryState = QStart;
static volatile uint32_t queryDelayStart;
static volatile uint32_t bulkInStarted;

static volatile uint32_t iCmdResponse;
static uint8_t const *iCmdResponseBuf;
static size_t iCmdResponseBufLen;

static uint32_t resp_delay = 125u; // Adjustable delay, to allow for better testing
static size_t buffer_len;
static size_t buffer_tx_ix; // for transmitting using multiple transfers
static uint8_t buffer[225]; // A few packets long should be enough.

#if (CFG_TUD_USBTMC_ENABLE_488)
static usbtmc_response_capabilities_488_t const
#else
static usbtmc_response_capabilities_t const
#endif
tud_usbtmc_app_capabilities  =
{
    .USBTMC_status = USBTMC_STATUS_SUCCESS,
    .bcdUSBTMC = USBTMC_VERSION,
    .bmIntfcCapabilities =
    {
        .listenOnly = 0,
        .talkOnly = 0,
        .supportsIndicatorPulse = 1
    },
    .bmDevCapabilities = {
        .canEndBulkInOnTermChar = 0
    },

#if (CFG_TUD_USBTMC_ENABLE_488)
    .bcdUSB488 = USBTMC_488_VERSION,
    .bmIntfcCapabilities488 =
    {
        .supportsTrigger = 1,
        .supportsREN_GTL_LLO = 0,
        .is488_2 = 1
    },
    .bmDevCapabilities488 =
    {
      .SCPI = 1,
      .SR1 = 0,
      .RL1 = 0,
      .DT1 =0,
    }
#endif
};

static usbtmc_msg_dev_dep_msg_in_header_t rspMsg = {
    .bmTransferAttributes =
    {
      .EOM = 1,
      .UsingTermChar = 0
    }
};


#endif
