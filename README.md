# Clipper: A SSH Clipboard Synchronizer

## Overview

Clipper is a clipboard synchronizing tool between Windows and Linux. The desired use case will be a windows local machine controlling a Linux remote server via ssh. However, other usage scenarios may be incorporated in the future.

## Ideology

Instead of storing clip records on one centralized server, clipper keeps both machines' clipboards intact. Otherwise, a delay may occur while pasting content. This means that every 'copy' operation is monitored and synced with the remote machine immediately.

## Implementation

As the local machine controls the remote server in the terminal, OSC, or Operating System commands can be utilized to send clipboard records to the local machine. Submitting local records can be achieved by ssh commands (safer) or raw HTTP requests (faster).

## Development

1. Get the bits and peices running: osc52 components and windows clipboard monitor.	<- Current Phase
1. Integrate and test the package.
1. Polishing the software, ex: adding log system, run in system tray, etc.
1. Expanding the usage scenarios, ex: mutiple clients, ssh forwarding, etc.

The project is now under development.
