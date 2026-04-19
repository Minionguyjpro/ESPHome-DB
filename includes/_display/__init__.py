import esphome.config_validation as cv
import esphome.codegen as cg


def _validate(config):
    # A bare `_display:` in YAML produces None; treat it as an empty dict.
    if config is None:
        config = {}
    return cv.Schema({})(config)


CONFIG_SCHEMA = _validate


async def to_code(config):
    cg.add_global(cg.RawExpression('#include "display.h"'))
