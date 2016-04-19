DROP TABLE IF EXISTS `store_items`;

CREATE TABLE `store_items` (
  `id` int(11) NOT NULL,
  `cat_id` int(11) NOT NULL,
  `item_entry` int(11) NOT NULL,
  `price` int(11) NOT NULL,
  `quantity` int(11) NOT NULL DEFAULT '1',
  `required_avg_item_level` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `FK_CAT_ID` (`cat_id`),
  CONSTRAINT `FK_CAT_ID` FOREIGN KEY (`cat_id`) REFERENCES `store_categories` (`cat_id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;