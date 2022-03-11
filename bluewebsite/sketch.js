// Credit for this goes to https://itpnyu.github.io/p5ble-website/docs/read-one-char-callback
/**
 * recreate own version i understand better with newer things not p5
 * https://web.dev/bluetooth/
 * https://developer.mozilla.org/en-US/docs/Web/API/Web_Bluetooth_API#browser_compatibility
 * 
 * 2c7e6fb1-5667-a59f-07ec-72b13e80f685
 */// The serviceUuid must match the serviceUuid of the device you would like to connect
 function onButtonClick() {
  let serviceUuid = document.querySelector('#service').value;
  if (serviceUuid.startsWith('0x')) {
    serviceUuid = parseInt(serviceUuid);
  }

  let characteristicUuid = document.querySelector('#characteristic').value;
  if (characteristicUuid.startsWith('0x')) {
    characteristicUuid = parseInt(characteristicUuid);
  }

  log('Requesting Bluetooth Device...');
  navigator.bluetooth.requestDevice({filters: [{services: [serviceUuid]}]})
  .then(device => {
    log('Connecting to GATT Server...');
    return device.gatt.connect();
  })
  .then(server => {
    log('Getting Service...');
    return server.getPrimaryService(serviceUuid);
  })
  .then(service => {
    log('Getting Characteristic...');
    return service.getCharacteristic(characteristicUuid);
  })
  .then(characteristic => {
    log('Getting Descriptors...');
    return characteristic.getDescriptors();
  })
  .then(descriptors => {
    log('> Descriptors: ' +
      descriptors.map(c => c.uuid).join('\n' + ' '.repeat(19)));
  })
  .catch(error => {
    log('Argh! ' + error);
  });
}