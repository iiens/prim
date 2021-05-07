"use strict";

const assert = require('assert');
const {Logger} = require("../src/model/logger");

describe('Logger', function() {
    describe('#EcritureFile', function() {
        it('should return -1 when the value is not present', function() {
            let logger = Logger.Instance;
            assert.notEqual(logger, undefined);

            logger.level = Logger.Levels.Debug;
            logger.info("Attention test de level info");
            logger.debug("Attention test de level debug");
            logger.warn("Attention test de level warning");
            logger.error("Attention test de level error");
        });
    });
})