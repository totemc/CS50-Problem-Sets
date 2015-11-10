<?php

    // configuration
    require("../includes/config.php"); 
    
    $positions = [];
    // query stocks
    $rows = query("SELECT symbol,shares FROM portfolio WHERE id = ?", $_SESSION["id"]);
    // query cash
    $cash = query("SELECT cash FROM users WHERE id=?", $_SESSION["id"]);
    
    // store in new array
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => $stock["price"],
                "shares" => $row["shares"],
                "symbol" => $row["symbol"],
                "total" => $row["shares"] * $stock["price"]
            ];
        }
    }
    
    // render portfolio
    render("portfolio.php", ["positions" => $positions, "title" => "Portfolio","cash" => $cash]);
    

?>
