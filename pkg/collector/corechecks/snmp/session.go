package snmp

import (
	"github.com/soniah/gosnmp"
	"time"
)

type snmpSession struct {
	gosnmpInst gosnmp.GoSNMP
}

func buildSession(config snmpConfig) snmpSession {
	gosnmpInst := gosnmp.GoSNMP{
		Target:             config.IPAddress,
		Port:               config.Port,
		Community:          config.CommunityString,
		Version:            gosnmp.Version2c,
		Timeout:            time.Duration(2) * time.Second,
		Retries:            3,
		ExponentialTimeout: true,
		MaxOids:            100,
	}

	return snmpSession{gosnmpInst}
}

func (s *snmpSession) Get(oids []string) (result *gosnmp.SnmpPacket, err error) {
	return s.gosnmpInst.Get(oids)
}