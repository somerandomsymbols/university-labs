var WebSocketServer = require('ws').Server,
  wss = new WebSocketServer({port: 40510})

var os = require('os');

wss.on('connection', function (ws) {
  ws.on('message', function (message) {
    console.log('received: %s', message)
  })

  setInterval(
    () => ws.send(`${JSON.stringify({avg:os.loadavg(), memory:os.totalmem(), free:os.freemem()})}`),
    1000
  )
})
