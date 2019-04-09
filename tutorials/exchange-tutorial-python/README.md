The following steps must be taken for the example script to work.

0. Create wallet
0. Create account for fscio.token
0. Create account for scott
0. Create account for exchange
0. Set token contract on fscio.token
0. Create FSC token
0. Issue initial tokens to scott

**Note**:
Deleting the `transactions.txt` file will prevent replay from working.


### Create wallet
`clfsc wallet create`

### Create account steps
`clfsc create key`

`clfsc create key`

`clfsc wallet import  --private-key <private key from step 1>`

`clfsc wallet import  --private-key <private key from step 2>`

`clfsc create account fscio <account_name> <public key from step 1> <public key from step 2>`

### Set contract steps
`clfsc set contract fscio.token /contracts/fscio.token -p fscio.token@active`

### Create FSC token steps
`clfsc push action fscio.token create '{"issuer": "fscio.token", "maximum_supply": "100000.0000 FSC", "can_freeze": 1, "can_recall": 1, "can_whitelist": 1}' -p fscio.token@active`

### Issue token steps
`clfsc push action fscio.token issue '{"to": "scott", "quantity": "900.0000 FSC", "memo": "testing"}' -p fscio.token@active`
