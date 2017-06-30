const bleno = require('bleno')
const i2c = require('i2c');

const address = 0x08;
const wire = new i2c(address, {device: '/dev/i2c-1'});

const toBufferArray = function (json) {
  let buf = Buffer.from(JSON.stringify(json));
  return buf.toJSON().data;
}

const serviceUuid = '5ABF9F0B-338C-4C9F-871A-02074BB0D71D'
const lightCharUuid = '5ABF9F0B-338C-4C9F-871A-02074BB0D71E'

const lightCharacteristic = new bleno.Characteristic({
  value: null,
  uuid: lightCharUuid,
  properties: ['write'],
  onWriteRequest: function(data, offset, withoutResponse, callback) {
      let json = {'light': data.readInt8(0)}
      console.log(json)
      wire.write(toBufferArray(json), function (err) {});
      callback(this.RESULT_SUCCESS);
    }  
});

bleno.on('stateChange', function(state) {
  console.log('State change: ' + state);
  if (state === 'poweredOn') {
    bleno.startAdvertising('LightService', [serviceUuid]);
  } else {
    bleno.stopAdvertising();
  }
});

bleno.on('accept', function(clientAddr) {
  console.log('Accepted connection from address:', clientAddr);
});

bleno.on('disconnect', function(clientAddr) {
  console.log('Disconnected from address:', clientAddr);
});

bleno.on('advertisingStart', function(err) {
  if (err) {
    console.error(err);
  } else {
    console.log('Advertising start success');
    bleno.setServices([
      new bleno.PrimaryService({
        uuid: serviceUuid,
        characteristics: [
          lightCharacteristic,
        ]
      }),
    ]);
  }
});
