package cf.jeanbisel.wipmod;

import net.minecraft.world.WorldServer;
import net.minecraft.entity.Entity;
import net.minecraft.init.Blocks;
import net.minecraft.util.math.BlockPos;



public class WIPTeleporter extends net.minecraft.world.Teleporter
{
    /** A private ﻿Random() function in Teleporter */
	protected final WorldServer world;
    public WIPTeleporter(WorldServer worldIn)
    {
        super(worldIn);
        this.world = worldIn;
    }

    public void placeInPortal(Entity entity, float yaw){
        BlockPos pos = new BlockPos(entity.posX, 256, entity.posZ);
        entity.motionX = 0.0D;
        entity.motionY = 0.0D;
        entity.motionZ = 0.0D;
        while ( world.getBlockState(pos.down(1)).getBlock() == Blocks.AIR){
            pos=pos.down(1);
        }
        entity.setLocationAndAngles(entity.posX, pos.getY()+1, entity.posZ, entity.rotationYaw, 0.0F);

    }

}
