#!/bin/sh

curl -i -X POST 172.16.0.107:9191 -H "Content-Type: text/xml" --data "@mm7.DeliverReq.req.xml"
