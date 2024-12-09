# Uniswap v4 Address Miner

This repository contains a C++ program to mine Ethereum contract addresses for the **Uniswap v4 Address Mining Challenge**. The program calculates the score of Ethereum addresses based on the specified rules and saves the results in a `.txt` file.

## Features

- Generates **1000000 random salts** to compute Ethereum addresses.
- Scores addresses based on the **Uniswap v4 scoring rules**:
  - 10 points for each leading 0 nibble.
  - 40 points if the address starts with "4444".
  - 20 points if the first nibble after "4444" is not a 4.
  - 20 points if the last 4 nibbles are all 4s.
  - 1 point for each 4 elsewhere in the address.
- Sorts the addresses by **score in descending order**.
- Saves the results to `uniswap_v4_addresses_sorted.txt` on your **Desktop**.

---

## Requirements

Before you begin, ensure you have the following installed:

1. **g++ Compiler** (supports C++11 or higher).
2. **Crypto++ Library**:
   - Linux users can install it via their package manager (e.g., `libcrypto++-dev`).
3. **WSL (Windows Subsystem for Linux)**:
   - Required for Windows users to run Linux commands.

---

## Installation and Usage

### Step 1: Clone the Repository

Open your terminal and clone the repository:

```bash
git clone https://github.com/AzrielTheHellrazor/uniswap_v4_address_miner.git
cd uniswap_v4_address_miner
```

### Step 2: Install Dependencies

1. On **Ubuntu/WSL**, run:

   ```bash
   sudo apt update
   sudo apt install build-essential libcrypto++-dev

   ```

2. Verify the Crypto++ installation:
   ```bash
   dpkg -l | grep crypto++
   ```

### Step 3: Compile the Program

    Compile the program using:

```bash
g++ -std=c++11 -o address_miner address_miner.cpp -lcrypto++ -lpthread
```

This will create an executable file named `address_miner`.

### Step 4: Run the Program

Run the program:

```bash
./address_miner
```
The program will:

Generate 1,000,000 random Ethereum addresses.
Score the addresses based on the challenge rules.
Sort the results by score in descending order.
Save the results to a file named uniswap_v4_addresses_sorted.txt on your Desktop.

