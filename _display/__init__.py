import esphome.config_validation as cv
import esphome.codegen as cg

# Allow use as external component without any additional settings.
# cv.ensure_dict coerces a bare `_display:` (None) to {} before validation.
CONFIG_SCHEMA = cv.All(cv.ensure_dict, cv.Schema({}))


async def to_code(config):
    cg.add_global(cg.RawExpression('#include "display.h"'))
