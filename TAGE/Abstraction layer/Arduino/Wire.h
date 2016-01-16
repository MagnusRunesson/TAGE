#ifndef __WIRE_H__
#define __WIRE_H__

#include <cstdint>
#include <unordered_map>

class II2CSlaveDevice
{
public:
	virtual void i2cWriteData( uint8_t ) = 0;
	virtual uint8_t i2cReadData( uint8_t reg ) = 0;
};


class SimWire
{
public:
	SimWire(bool verbose = false);

	bool AddDevice(II2CSlaveDevice*, uint32_t address);

	void begin();
	void beginTransmission(uint32_t address);
	void endTransmission();
	void requestFrom(uint32_t address, uint8_t reg);
	uint8_t read();
	void write(uint8_t);


private:
	// For now we have only one device, so that is what I'm testing.
	II2CSlaveDevice* current_slave_;
	std::unordered_map<uint32_t,II2CSlaveDevice*> devices_;
	bool verbose_;

	uint8_t readReg_;

};

extern uint8_t TWBR;

extern SimWire Wire;


#endif
