<?php


if(($_GET["apikey"]) == "0295436285034")
{
	if(isset($_GET["content"]))
	{
		if(($_GET["content"]) == "on")
		{
		echo shell_exec('sudo WS on');
		echo "200(1)";
		}
		else
		{
		echo shell_exec('sudo WS off');
		echo "200(2)";
		}
	}
}
else
{
echo "Autorization error";
}

?>
