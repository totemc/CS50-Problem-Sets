<?php
    // configuration
    require("../includes/config.php");
    
    // Query session shares
    $rows = query("SELECT CASE WHEN type = 0 THEN 'SELL' ELSE 'BUY' END action, symbol, shares, price, date FROM history
        WHERE id = ? order by date desc", $_SESSION["id"]);
    
    if (count($rows) == 0)
    {
        apologize("No recorded transactions for this user exist.");
    }
    // render history form
    render("history_form.php", ["title" => "History", "history" => $rows]);
?>
