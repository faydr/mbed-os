/** @file
 * Copyright (c) 2018-2019, Arm Limited or its affiliates. All rights reserved.
 * SPDX-License-Identifier : Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
**/

#include "val_crypto.h"

typedef struct {
    char                    test_desc[50];
    psa_algorithm_t         alg;
    char                    input;
    size_t                  input_length;
    char                    hash[32];
    size_t                  hash_length;
    psa_status_t            expected_status;
} test_data;

static const char sha384_hash[] = {
0x43, 0x72, 0xe3, 0x8a, 0x92, 0xa2, 0x8b, 0x5d, 0x2c, 0x39, 0x1e, 0x62,
0x45, 0x2a, 0x86, 0xd5, 0x0e, 0x02, 0x67, 0x22, 0x8b, 0xe1, 0x76, 0xc7, 0x7d, 0x24, 0x02, 0xef,
0xfe, 0x9f, 0xa5, 0x0d, 0xe4, 0x07, 0xbb, 0xb8, 0x51, 0xb3, 0x7d, 0x59, 0x04, 0xab, 0xa2, 0xde,
0xde, 0x74, 0xda, 0x2a};

static const char sha512_hash[] = {
0x29, 0x6e, 0x22, 0x67, 0xd7, 0x4c, 0x27, 0x8d, 0xaa, 0xaa, 0x94, 0x0d,
0x17, 0xb0, 0xcf, 0xb7, 0x4a, 0x50, 0x83, 0xf8, 0xe0, 0x69, 0x72, 0x6d, 0x8c, 0x84, 0x1c, 0xbe,
0x59, 0x6e, 0x04, 0x31, 0xcb, 0x77, 0x41, 0xa5, 0xb5, 0x0f, 0x71, 0x66, 0x6c, 0xfd, 0x54, 0xba,
0xcb, 0x7b, 0x00, 0xae, 0xa8, 0x91, 0x49, 0x9c, 0xf4, 0xef, 0x6a, 0x03, 0xc8, 0xa8, 0x3f, 0xe3,
0x7c, 0x3f, 0x7b, 0xaf};

static test_data check1[] = {
#ifdef ARCH_TEST_MD2
{"Test psa_hash_verify with MD2 algorithm\n",
 PSA_ALG_MD2, 0xbd, 1,
 {0x8c, 0x9c, 0x17, 0x66, 0x5d, 0x25, 0xb3, 0x5f, 0xc4, 0x13, 0xc4, 0x18, 0x05, 0xc6, 0x79, 0xcf},
 16, PSA_SUCCESS,
},
#endif

#ifdef ARCH_TEST_MD4
{"Test psa_hash_verify with MD4 algorithm\n",
 PSA_ALG_MD4, 0xbd, 1,
 {0x18, 0xc3, 0x3f, 0x97, 0x29, 0x7e, 0xfe, 0x5f, 0x8a, 0x73, 0x22, 0x58, 0x28, 0x9f, 0xda, 0x25},
 16, PSA_SUCCESS,
},
#endif

#ifdef ARCH_TEST_MD5
{"Test psa_hash_verify with MD5 algorithm\n",
 PSA_ALG_MD5, 0xbd, 1,
 {0xab, 0xae, 0x57, 0xcb, 0x56, 0x2e, 0xcf, 0x29, 0x5b, 0x4a, 0x37, 0xa7, 0x6e, 0xfe, 0x61, 0xfb},
 16, PSA_SUCCESS,
},
#endif

#ifdef ARCH_TEST_RIPEMD160
{"Test psa_hash_verify with RIPEMD160 algorithm\n",
 PSA_ALG_RIPEMD160, 0xbd, 1,
 {0x50, 0x89, 0x26, 0x5e, 0xe5, 0xd9, 0xaf, 0x75, 0xd1, 0x2d, 0xbf, 0x7e, 0xa2, 0xf2, 0x7d, 0xbd,
  0xee, 0x43, 0x5b, 0x37},
 20, PSA_SUCCESS,
},
#endif

#ifdef ARCH_TEST_SHA1
{"Test psa_hash_verify with SHA1 algorithm\n",
 PSA_ALG_SHA_1, 0xbd, 1,
 {0x90, 0x34, 0xaa, 0xf4, 0x51, 0x43, 0x99, 0x6a, 0x2b, 0x14, 0x46, 0x5c, 0x35, 0x2a, 0xb0, 0xc6,
  0xfa, 0x26, 0xb2, 0x21},
 20, PSA_SUCCESS,
},
#endif

#ifdef ARCH_TEST_SHA224
{"Test psa_hash_verify with SHA224 algorithm\n",
 PSA_ALG_SHA_224, 0xbd, 1,
 {0xb1, 0xe4, 0x6b, 0xb9, 0xef, 0xe4, 0x5a, 0xf5, 0x54, 0x36, 0x34, 0x49, 0xc6, 0x94, 0x5a, 0x0d,
  0x61, 0x69, 0xfc, 0x3a, 0x5a, 0x39, 0x6a, 0x56, 0xcb, 0x97, 0xcb, 0x57},
 28, PSA_SUCCESS,
},
#endif

#ifdef ARCH_TEST_SHA256
{"Test psa_hash_verify with SHA256 algorithm\n",
 PSA_ALG_SHA_256, 0xbd, 1,
 {0x68, 0x32, 0x57, 0x20, 0xaa, 0xbd, 0x7c, 0x82, 0xf3, 0x0f, 0x55, 0x4b, 0x31, 0x3d, 0x05, 0x70,
  0xc9, 0x5a, 0xcc, 0xbb, 0x7d, 0xc4, 0xb5, 0xaa, 0xe1, 0x12, 0x04, 0xc0, 0x8f, 0xfe, 0x73, 0x2b},
 32, PSA_SUCCESS,
},
#endif

#ifdef ARCH_TEST_SHA384
{"Test psa_hash_verify with SHA384 algorithm\n",
 PSA_ALG_SHA_384, 0xbd, 1, {0}, 48, PSA_SUCCESS,
},
#endif

#ifdef ARCH_TEST_SHA512
{"Test psa_hash_verify with SHA512 algorithm\n",
 PSA_ALG_SHA_512, 0xbd, 1, {0}, 64, PSA_SUCCESS,
},
#endif

#ifdef ARCH_TEST_SHA256
{"Test psa_hash_verify with incorrect expected hash\n",
 PSA_ALG_SHA_256, 0xbd, 1,
 {0x68, 0x32, 0x57, 0x20, 0xab, 0xbd, 0x7c, 0x82, 0xf3, 0x0f, 0x55, 0x4b, 0x31, 0x3d, 0x05, 0x70,
  0xc9, 0x5a, 0xcc, 0xbb, 0x7d, 0xc4, 0xb5, 0xaa, 0xe1, 0x12, 0x04, 0xc0, 0x8f, 0xfe, 0x73, 0x78},
 32, PSA_ERROR_INVALID_SIGNATURE,
},

{"Test psa_hash_verify with incorrect hash length\n",
 PSA_ALG_SHA_256, 0xbd, 1,
 {0x68, 0x32, 0x57, 0x20, 0xaa, 0xbd, 0x7c, 0x82, 0xf3, 0x0f, 0x55, 0x4b, 0x31, 0x3d, 0x05, 0x70,
  0xc9, 0x5a, 0xcc, 0xbb, 0x7d, 0xc4, 0xb5, 0xaa, 0xe1, 0x12, 0x04, 0xc0, 0x8f, 0xfe, 0x73, 0x2b},
 31, PSA_ERROR_INVALID_SIGNATURE,
},
#endif
};