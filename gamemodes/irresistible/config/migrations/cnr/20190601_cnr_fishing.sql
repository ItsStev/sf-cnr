-- CREATE A MIGRATION ENTRY
INSERT INTO `DB_MIGRATIONS` (`MIGRATION`) VALUES ('20190601_cnr_fishing');

-- BEGIN

-- CREATE TABLE
CREATE TABLE IF NOT EXISTS `FISH_DATA` (
  `USER_ID` int(11) NOT NULL,
  `PLAT` int(7) NOT NULL DEFAULT '0',
  `FRESH` int(7) NOT NULL DEFAULT '0',
  `PEPPER` int(7) NOT NULL DEFAULT '0',
  `MASKED` int(7) NOT NULL DEFAULT '0',
  `BLADEFIN` int(7) NOT NULL DEFAULT '0',
  `GOLDEN` int(7) NOT NULL DEFAULT '0',
  `NEPTUNE` int(7) NOT NULL DEFAULT '0',
  `NAMI` int(7) NOT NULL DEFAULT '0',
  `FLATHEAD` int(7) NOT NULL DEFAULT '0',
  `IRON` int(7) NOT NULL DEFAULT '0',
  `CLARION` int(7) NOT NULL DEFAULT '0',
  PRIMARY KEY (`USER_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
COMMIT;