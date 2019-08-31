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
import net.minecraft.block.SoundType;

public class WIPDirt extends Block
{
    public WIPDirt()
    {
        super(Material.GROUND);
        this.setRegistryName("wipmod:wipdirt");
        this.setUnlocalizedName("wipmod.wipdirt");
        this.setCreativeTab(CreativeTabs.BUILDING_BLOCKS);
		this.setHardness(0.5F);
		this.setSoundType(SoundType.GROUND);
		this.setHarvestLevel("shovel",0);
    }
}
