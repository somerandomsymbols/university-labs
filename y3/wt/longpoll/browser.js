// Sending messages, a simple POST
/*function PublishForm(form, url) {

  function sendMessage(message) {
    fetch(url, {
      method: 'POST',
      body: message
    });
  }

  setInterval(
      function() {
          let message = form.message.value;
          if (message) {
            form.message.value = '';
            sendMessage(message);
          }
          return false;
        },
      1000
    );
}*/

// Receiving messages with long polling
function SubscribePane(elem, url) {

  function showMessage(message) {
var cpu = JSON.parse(message);
    document.getElementById('appout').innerHTML = '<b>MINUTE AVERAGE LOAD:</b> ' + cpu.avg[0] + ';<br /><b>TOTAL MEMORY:</b> ' + cpu.memory + ';<br /><b>FREE MEMORY:</b> ' + cpu.free;

  }

  async function subscribe() {
    let response = await fetch(url);

    if (response.status == 502) {
      // Connection timeout
      // happens when the connection was pending for too long
      // let's reconnect
      await subscribe();
    } else if (response.status != 200) {
      // Show Error
      showMessage(response.statusText);
      // Reconnect in one second
      await new Promise(resolve => setTimeout(resolve, 1000));
      await subscribe();
    } else {
      // Got message
      let message = await response.text();
      showMessage(message);
      await subscribe();
    }
  }

  subscribe();

}
