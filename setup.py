from distutils.core import setup, Extension

hive_hash_module = Extension('hive_hash',
                               sources = ['hivemodule.c',
                                          'hive.c',
					  'pomelo_x64.c',
										  'sha3/blake.c',
										  'sha3/keccak.c',
										  'sha3/shabal.c'],
                               include_dirs=['.', './sha3'])

setup (name = 'hive_hashs',
       version = '1.0',
       description = 'Bindings for scrypt proof of work used by Quarkcoin',
       ext_modules = [hive_hash_module])
