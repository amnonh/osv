#!/usr/bin/env python
import basetest

class testhardware(basetest.Basetest):
    def test_count_cpu(self):
        get_path = self.path_by_nick(self.env_hardware, "processorCount")
        val = self.curl(get_path)
        self.assertGreaterEqual(4,val)

    @classmethod
    def setUpClass(cls):
        cls.env_hardware = cls.get_json_api("hardware.json")
