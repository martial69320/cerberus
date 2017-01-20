SET @TEXT_ID := 65000;
INSERT INTO `npc_text` (`ID`, `text0_0`) VALUES
(@TEXT_ID, 'La transmogrification vous permet de modifier l\'apparance de votre équipement sans modifier les stats de celui-ci.\r\nLes objets utilisés dans la transmogrification ne sont plus remboursables, échangeable et sont liés à vous.\r\nLa mise à jour d\'un menu met à jour la vue et les prix.\r\n\r\nLes restrictions comprennent, sans s\'y limiter:\r\nSeules les armures et les armes peuvent être transmogrifiées\r\nFusils, Arcs et arbalètes peuvent être transmogrifiés entre eux\r\nLes cannes à pêche ne peuvent être transmogrifiés\r\nVous devez être en mesure d\'équiper les deux objets utilisés dans le processus.\r\n\r\nLes transmogrifications restent sur vos objets aussi longtemps que vous les possédez.\r\nSi vous essayez de mettre l\'objet dans la banque de guilde ou de le poster à quelqu\'un d\'autre, la transmogrification est supprimée.\r\n\r\nVous pouvez également supprimer les transmogrifications gratuitement au transmogrificateur.'),
(@TEXT_ID+1, 'Vous pouvez enregistrer vos propres ensembles de transmogrification.\r\n\r\nPour enregistrer, vous devez d\'abord transmogrifier vos objets équipés.\r\nPuis, lorsque vous allez dans le menu de gestion des sets, et que vous allez dans "Enregistrer le set",\r\ntous les objets que vous avez transmogrifiés sont affichés afin que vous voyez ce que vous enregistrez.\r\nSi vous pensez que l\'ensemble est bien, vous pouvez cliquer pour enregistrer l\'ensemble et le nommer comme vous le souhaitez.\r\n\r\nPour utiliser un ensemble, vous pouvez cliquer sur l\'ensemble enregistré dans le menu de gestion des ensembles, puis sélectionner "Utiliser set".\r\nSi l\'ensemble a une transmogrification pour un objet déjà transmogrifié, l\'ancienne est perdue.\r\nNotez que les mêmes restrictions de transmogrification s\'appliquent lorsque vous tentez d\'utiliser un ensemble comme dans la transmogrification normale.\r\n\r\nPour supprimer un ensemble, vous pouvez aller dans le gestionnaire de set et cliquer sur "Supprimer".');

SET @STRING_ENTRY := 11100;
INSERT INTO `trinity_string` (`entry`, `content_default`) VALUES
(@STRING_ENTRY+0, 'Objet transmogrifié avec succès.'),
(@STRING_ENTRY+1, 'L\'emplacement de l\'équipement est vide.'),
(@STRING_ENTRY+2, 'L\'objet source selectionné est incorrects.'),
(@STRING_ENTRY+3, 'L\'objet source est inexistant.'),
(@STRING_ENTRY+4, 'L\'emplacement de destination n\'existe pas.'),
(@STRING_ENTRY+5, 'Les objets sélectionnés sont incorrects.'),
(@STRING_ENTRY+6, 'Vous n\'avez pas assez d\'or.'),
(@STRING_ENTRY+7, 'Vous n\'avez pas assez de Token.'),
(@STRING_ENTRY+8, 'Transmogrifications supprimée avec succès.'),
(@STRING_ENTRY+9, 'Il n\'y as pas de transmogrifications.'),
(@STRING_ENTRY+10, 'Le nom d\'ensemble est incorrect.');
