import esphome.config_validation as cv
import esphome.codegen as cg

# Allow use as external component without any additional settings
CONFIG_SCHEMA = cv.Schema({})


async def to_code(config):
    cg.add_global(cg.RawExpression('#include "_display/display.h"'))
