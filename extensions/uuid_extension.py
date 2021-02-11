#!/usr/bin/env python
import uuid
from jinja2.ext import Extension


class UUIDExtension(Extension):
    def __init__(self, environment):
        super(UUIDExtension, self).__init__(environment)

        def gen_uid():
            cid = uuid.uuid4().hex
            vst_uid = ",".join(['0x' + cid[n*8:(n+1)*8] for n in range(4)])
            return vst_uid

        environment.globals.update(processor_uid=gen_uid())
        environment.globals.update(controller_uid=gen_uid())
