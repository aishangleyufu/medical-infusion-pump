----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    21:31:49 07/27/2015 
-- Design Name: 
-- Module Name:    fenping2 - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

---- Uncomment the following library declaration if instantiating
---- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity fenping2 is
    Port ( F50M : in  STD_LOGIC;
           CS : out  STD_LOGIC;
           SCLK : out  STD_LOGIC
			  );
end fenping2;

architecture Behavioral of fenping2 is

SIGNAL SCLK_TMP,CS_TMP:STD_LOGIC;
begin
P1:process(F50M)

variable cnt500:integer range 0 to 500;  
begin
  IF F50M'event and F50M='1' THEN
     IF cnt500<250 then
	    SCLK_TMP<='0';
	   ELSE
		  SCLK_TMP<='1';
	 END IF;
     IF (cnt500=500) THEN cnt500:=0;
     ELSE
       cnt500:=cnt500+1;
     END IF;
    END IF;
END PROCESS P1;
P2:process(SCLK_TMP)
variable cnt18:integer range 0 to 18; 
  BEGIN	 
   IF SCLK_TMP'EVENT AND SCLK_TMP='1' THEN
	   IF cnt18<2 THEN
		  CS_TMP<='1';
		ELSE
		  CS_TMP<='0';
		END IF;  
		IF (CNT18=18) THEN CNT18:=0;
		ELSE
		CNT18:=CNT18+1;
		END IF;
	END IF;
	END PROCESS P2;

SCLK<=CS_TMP or ((not CS_TMP) and SCLK_TMP);
CS<=CS_TMP;	
end Behavioral;

