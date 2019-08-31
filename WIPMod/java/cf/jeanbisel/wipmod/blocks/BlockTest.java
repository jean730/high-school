package cf.jeanbisel.wipmod.blocks;

import net.minecraft.block.Block;
import net.minecraft.block.material.Material;
import net.minecraft.creativetab.CreativeTabs;
import net.minecraft.util.math.BlockPos;
import net.minecraft.world.World;
import net.minecraft.util.EnumParticleTypes;
import net.minecraft.block.state.IBlockState;
import net.minecraft.entity.player.EntityPlayer;
import net.minecraft.util.EnumHand;
import net.minecraft.util.EnumFacing;
import net.minecraftforge.fml.relauncher.Side;
import net.minecraftforge.fml.relauncher.SideOnly;
import net.minecraft.entity.Entity;
import net.minecraftforge.common.util.ITeleporter;
import net.minecraft.world.DimensionType;
import net.minecraft.block.SoundType;
import net.minecraft.entity.player.EntityPlayerMP;
import cf.jeanbisel.wipmod.WIPTeleporter;
public class BlockTest extends Block
{
    public BlockTest()
    {
        super(Material.ROCK);
        this.setRegistryName("wipmod:blocktest");
        this.setUnlocalizedName("wipmod.blocktest");
        this.setCreativeTab(CreativeTabs.BUILDING_BLOCKS);
        this.setLightOpacity(0);
        this.setLightLevel(1);
        this.setTickRandomly(true);
        this.setHardness(1.5F);
        this.setResistance(10.0F);
        this.setSoundType(SoundType.STONE);
    }
    public void onEntityWalk(World worldIn, BlockPos posblock, Entity entityIn)
    {
        for(double i=0;i<5;i+=1){
        worldIn.spawnParticle(EnumParticleTypes.FLAME, (double)(entityIn.posX+0.2D), (double)(entityIn.posY+0D), (double)(entityIn.posZ-0.2D), 0 /*speedX*/, 0.1D /*speedY*/, 0 /*speedZ*/);
        worldIn.spawnParticle(EnumParticleTypes.FLAME, (double)(entityIn.posX-0.2D), (double)(entityIn.posY+0D), (double)(entityIn.posZ-0.2D), 0 /*speedX*/, 0.1D /*speedY*/, 0 /*speedZ*/);
        worldIn.spawnParticle(EnumParticleTypes.FLAME, (double)(entityIn.posX-0.2D), (double)(entityIn.posY+0D), (double)(entityIn.posZ+0.2D), 0 /*speedX*/, 0.1D /*speedY*/, 0 /*speedZ*/);
        worldIn.spawnParticle(EnumParticleTypes.FLAME, (double)(entityIn.posX+0.2D), (double)(entityIn.posY+0D), (double)(entityIn.posZ+0.2D), 0 /*speedX*/, 0.1D /*speedY*/, 0 /*speedZ*/);

        }
		if (!entityIn.world.isRemote && entityIn instanceof EntityPlayerMP) {
				EntityPlayerMP Player = (EntityPlayerMP)entityIn;
				int dimId = DimensionType.byName("wipworld").getId();
				if(entityIn.dimension==0){
					WIPTeleporter teleporter = new WIPTeleporter(Player.mcServer.getWorld(dimId));
					Player.mcServer.getPlayerList().transferPlayerToDimension(Player, dimId, teleporter);

				}
				else if(entityIn.dimension==dimId){
					dimId=0;
					WIPTeleporter teleporter = new WIPTeleporter(Player.mcServer.getWorld(dimId));
					Player.mcServer.getPlayerList().transferPlayerToDimension(Player, dimId, teleporter);
				
				}
		}
    }
}
