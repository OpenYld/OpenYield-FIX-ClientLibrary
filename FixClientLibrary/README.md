# OpenYield Fix Client Library

This project is an **example** C++ library that implements a FIX client for the OpenYield Marketplace ([https://openyld.com](https://openyld.com)).

It contains sample code to

- Receive Market Data
- Receive Order Book messages
- Send Orders
- Handle Execution Events, including
    - Order Acknowledgements
    - Order Rejections
    - Fills
    - Post Trade Cancel and Correct
- Request and Receive a supported security list
- Receive Marketplace status messages
- Send Cancel All

It does not contain

- The FIX Wrapper to run the client
- Configurations to connect to OpenYield
- The Fixed Income Quote flow (yet) 

## Sample Usage

1. Create a subclass of `WorkflowInterface` and override the functions you need to receive the data. Use the parent functions to send messages.
2. Launch the `FixEngine` using the default QuickFix Model

```
  std::shared_ptr<INHERITED FROM WORKFLOWINTERFACE> workflow(COMPID>;
  
  // Setup a Fix Connection
  FIX::SessionSettings settings(
    <YOUR CONFIG FILE PATH>, true
  );

  FixEngine fixApplication(workflow);

  FIX::FileStoreFactory storeFactory(settings);
  FIX::FileLogFactory logFactory(settings);
  FIX::SocketInitiator initiator(fixApplication, storeFactory,
    settings, logFactory);

  // Start QuickFix and listen
  initiator.start();
```

## Dependencies

- Tested using Apple Clang 15 on MacOS and GCC 11.4.0 on Ubuntu 20
- Cmake
- FMT Format Library
- QuickFix Fix Engine

## Building

1. Download and build QuickFix as per [https://github.com/quickfix/quickfix](https://github.com/quickfix/quickfix)
2. Download and build FMT as per [https://github.com/quickfix/quickfix](https://github.com/quickfix/quickfix)

```
cd <YourPath>/OpenYield-FIX-ClientLibrary
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
```

## Cleaning

```
cd <YourPath>/OpenYield-FIX-ClientLibrary
rm -fr build
```

### The MIT License

Copyright 2024 OpenYield Inc

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

- The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

