DELETE FROM `trinity_string` WHERE `entry` IN (15000, 15001, 15002, 15003, 15004);
INSERT INTO `trinity_string` VALUES ('15004', 'Current XpKill Rate: %f.$BCurrent XpQuest Rate: %f.', null, null, null, null, null, null, null, null);
INSERT INTO `trinity_string` VALUES ('15003', 'The specified value is too low, it should be between 1 and 8.', null, null, null, null, null, null, null, null);
INSERT INTO `trinity_string` VALUES ('15001', 'XpQuest Rate set to %f ', null, null, null, null, null, null, null, null);
INSERT INTO `trinity_string` VALUES ('15002', 'The specified value is too high, it should be between 1 and 8.', null, null, null, null, null, null, null, null);
INSERT INTO `trinity_string` VALUES ('15000', 'XpKill Rate set to %f ', null, null, null, null, null, null, null, null);
DELETE FROM `command` WHERE `permission` IN (1010, 1011);
INSERT INTO `command` VALUES ('modify xpkill', '1010', 'Syntax: .modify xpkill #wert');
INSERT INTO `command` VALUES ('modify xpquest', '1011', 'Syntax: .modify xpquest #wert');