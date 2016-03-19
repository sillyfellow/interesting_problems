package utils

import "crypto/rand"
import "math/big"

func MyRand(max int64) int64 {
	nBig, _ := rand.Int(rand.Reader, big.NewInt(max))
	return nBig.Int64()
}
