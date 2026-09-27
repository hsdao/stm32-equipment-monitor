| ID | Required behavior | Acceptance target | Future test |

|---|---|---|---|

| REQ-01 | Acquire simulated measurements over SPI | Request every 100 ms during normal operation; record missed deadlines | Measure request intervals |

| REQ-02 | Reject corrupted packets | Corrupted packet never updates current readings; error counter increases | Deliberately alter a response byte |

| REQ-03 | Detect stale measurements | Enter communication fault at 500 ms without fresh valid data, allowing measured scheduling delay | Freeze the sample counter |

| REQ-04 | Recover communication | Clear fault after three consecutive valid fresh responses | Restore normal responses |

| REQ-05 | Display measurements and status | Schedule LCD refresh every 500 ms | Observe display while sending commands |

| REQ-06 | Process PC commands | Respond within 200 ms under normal operation | Send repeated `PING` commands |

| REQ-07 | Generate warnings and alarms | Follow documented threshold, persistence and hysteresis rules | Run simulated values across boundaries |

| REQ-08 | Continue without LCD | Acquisition and console remain operational | Start with LCD disconnected |

| REQ-09 | Handle invalid console input | Reject invalid input; accept the next valid command | Send an overlong line followed by `PING` |

| REQ-10 | Run reliably | Two hours without unexpected reset or lockup | Run a combined endurance test |

