#!/bin/bash
service nginx start
spawn-fcgi -p 8080 -n ./server
